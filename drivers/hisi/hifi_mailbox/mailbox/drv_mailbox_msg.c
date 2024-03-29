

/*****************************************************************************
1 ??????????
*****************************************************************************/
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_debug.h"
#include "drv_mailbox_gut.h"


/*****************************************************************************
	????????????????????C??????????????
*****************************************************************************/
#undef	_MAILBOX_FILE_
#define _MAILBOX_FILE_	 "msg"
/*****************************************************************************
  2 ????????????
*****************************************************************************/
/*lint -e715*/
int BSP_CPU_StateGet(int CpuID)
{
	return 1;
}
/*lint +e715*/

/*lint -e611*/
/*lint -e818*/
void mailbox_msg_receiver(void *mb_buf, void *handle, void *data)
{
	struct mb_queue * queue;  /*????buffer??????????????????????????*/
	struct mb_buff	* mbuf = ( struct mb_buff  *)mb_buf;
	mb_msg_cb  func = (mb_msg_cb)handle;

    queue = &mbuf->usr_queue;
    if (func) {
        func(data, (void *)queue, queue->size);
    } else {
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_READ_CALLBACK_NOT_FIND, mbuf->mailcode);
    }
}
/*lint +e611*/
/*lint +e818*/
MAILBOX_EXTERN unsigned int mailbox_reg_msg_cb(
                unsigned int             mailcode,
                mb_msg_cb                 func,
                void                     *data)
{
    return (unsigned int)mailbox_register_cb(mailcode, mailbox_msg_receiver, func, data);
}
/*lint -e801*/

MAILBOX_EXTERN unsigned int mailbox_try_send_msg(
                unsigned int            mailcode,
                const void              *pdata,
                unsigned int            length)
{
    struct mb_buff      *mb_buf = MAILBOX_NULL;
    struct mb_queue     *queue  = MAILBOX_NULL;
    int        ret_val    = MAILBOX_OK;

    if ((0 == pdata) || (0 == length)) {
        ret_val = mailbox_logerro_p1(MAILBOX_ERRO, mailcode);
        goto exit_out;

    }
    /*????????buffer*/
    ret_val = mailbox_request_buff(mailcode, (void *)&mb_buf);
    if (MAILBOX_OK != ret_val) {
        goto exit_out;
    }

    /*????????????*/
    queue = &mb_buf->usr_queue;
    if ( length != (unsigned int)mailbox_write_buff( queue, pdata, length)) {
         ret_val = mailbox_logerro_p1(MAILBOX_FULL, mailcode);
         goto exit_out;
    }

    /*????*/
    ret_val = mailbox_sealup_buff( mb_buf,  length);
    if (MAILBOX_OK == ret_val) {
         /*????????*/
        ret_val = mailbox_send_buff(mb_buf);
    }

exit_out:
    /*????????buffer*/
    if (MAILBOX_NULL != mb_buf) {
        mailbox_release_buff(mb_buf);
    }

    return (unsigned int)ret_val;
}

/*lint +e801*/

MAILBOX_GLOBAL unsigned int mailbox_read_msg_data(
                void                   *mail_handle,
                char                   *buff,
                unsigned int          *size)
{
    struct mb_queue *pMailQueue = (struct mb_queue *)mail_handle;

    if ((MAILBOX_NULL == pMailQueue) || (MAILBOX_NULL == buff) || (MAILBOX_NULL == size)) {
        return (unsigned int)mailbox_logerro_p1(MAILBOX_ERR_GUT_INPUT_PARAMETER, 0);
    }

    if (pMailQueue->size  >  *size) {
        return (unsigned int)mailbox_logerro_p1(MAILBOX_ERR_GUT_USER_BUFFER_SIZE_TOO_SMALL, *size);
    }

    /*??????????????????????????????????????*/
    if ((0 == pMailQueue->length) ||
        ((unsigned int)(pMailQueue->front - pMailQueue->base) >  pMailQueue->length ) ||
        ((unsigned int)(pMailQueue->rear - pMailQueue->base) >  pMailQueue->length )) {
        return (unsigned int)mailbox_logerro_p1(MAILBOX_CRIT_GUT_INVALID_USER_MAIL_HANDLE, pMailQueue);
    }

    *size =  (unsigned int)mailbox_read_buff(pMailQueue, buff, pMailQueue->size);

    return MAILBOX_OK;
}
/*lint -e838*/

extern bool is_hifi_loaded(void);
MAILBOX_EXTERN unsigned int mailbox_send_msg(
                unsigned int            mailcode,
                const void              *data,
                unsigned int            length)
{
	int  ret_val = MAILBOX_OK;
	unsigned int  try_go_on = MAILBOX_TRUE;
	int  try_times = 0;
	if (!is_hifi_loaded())
		return MAILBOX_HIFI_NOT_LOAD;
	ret_val= BSP_CPU_StateGet(mailbox_get_dst_id(mailcode));
	if (!ret_val) {
		return MAILBOX_TARGET_NOT_READY;
	}

	ret_val = (int)mailbox_try_send_msg(mailcode, data, length);

	if (MAILBOX_FALSE == mailbox_int_context()) {
		/*??????????????????*/
		while ((int)MAILBOX_FULL == ret_val) {
			mailbox_delivery(mailbox_get_channel_id(mailcode));
			try_go_on = (unsigned int)mailbox_scene_delay(MAILBOX_DELAY_SCENE_MSG_FULL, &try_times);

			if (MAILBOX_TRUE == try_go_on) {
				ret_val = (int)mailbox_try_send_msg(mailcode, data, length);
			} else {
				break;
			}
		}
	}

	if (MAILBOX_OK != ret_val) {
		/*mailbox_show(mailcode,0);*/
		/*mailbox_assert(ret_val);*/
		if ((int)MAILBOX_FULL != ret_val) {
			ret_val = (int)MAILBOX_ERRO;
		}
		return (unsigned int)ret_val;
	}

	return (unsigned int)ret_val;
}
/*lint +e838*/


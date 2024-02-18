

#ifndef __OAL_PCIE_COMM__
#define __OAL_PCIE_COMM__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*feature macro define*/
#include "oal_pcie_edma.h"
#include "oal_util.h"

#define PCIE_EDMA_FIFO_DEPTH            (4) /*fifo ??????4*/

#define PCIE_EDMA_WRITE_RINGBUF_SIZE    (16) /*refer to pcie_write_ringbuf_item*/
#define PCIE_EDMA_READ_RINGBUF_SIZE     (16) /*refer to pcie_read_ringbuf_item*/

#define PCIE_EDMA_READ_BUSRT_COUNT      (32) /*featch read buff every time*/
#define PCIE_EDMA_WRITE_BUSRT_COUNT     (32) /*featch read buff every time*/

#define PCIE_EDMA_ELEMENTS_EACH_BUFF    (2) /*how many elements each netbuf used!(mac header 64B + payload)*/

//#define PCIE_EDMA_TRANS_MAX_FRAME_LEN   (1544)
#define PCIE_EDMA_TRANS_MAX_FRAME_LEN   (1560)

#if (PCIE_EDMA_TRANS_MAX_FRAME_LEN%4)
#error PCIe dma element size must align to 4 bytes
#endif
#define PCIE_EDMA_FIFO_ELE_CNT  (PCIE_EDMA_FIFO_DEPTH+1)

/*Ringbuf ???????? ??????2??N????!*/
#define PCIE_EDMA_WRITE_RINGBUF_ITEMS          ((PCIE_EDMA_FIFO_DEPTH)*PCIE_EDMA_READ_BUSRT_COUNT)/*4*32*16=2048B*/
#define PCIE_EDMA_READ_NORMAL_RINGBUF_ITEMS    (PCIE_EDMA_FIFO_DEPTH*PCIE_EDMA_WRITE_BUSRT_COUNT)/*4*32*16=2048B*/
/*????????????????????????????????????????????(Host????)??
  ????????, ????????????????????????????????????????????????
  ??????????????????????????*/
#define PCIE_EDMA_READ_HIGH_RINGBUF_ITEMS      (32)/*????????????????????????, 32*16=512B*/

/*1 for linked list element, 2 for two channels*/
#ifdef _PRE_PLAT_FEATURE_PCIE_EDMA_FIFO
#define PCIE_EDMA_WRITE_MAX_ELEMENTS_EACH_CHAN  (PCIE_EDMA_WRITE_BUSRT_COUNT*PCIE_EDMA_ELEMENTS_EACH_BUFF/PCIE_EDMA_MAX_CHANNELS + 1)
#define PCIE_EDMA_READ_MAX_ELEMENTS_EACH_CHAN  (PCIE_EDMA_READ_BUSRT_COUNT*PCIE_EDMA_ELEMENTS_EACH_BUFF/PCIE_EDMA_MAX_CHANNELS + 1)
#define PCIE_EDMA_WRITE_CHAN_MAX_ELEMENTS (PCIE_EDMA_WRITE_MAX_ELEMENTS_EACH_CHAN*PCIE_EDMA_MAX_CHANNELS*PCIE_EDMA_FIFO_ELE_CNT)
#define PCIE_EDMA_READ_CHAN_MAX_ELEMENTS  (PCIE_EDMA_READ_MAX_ELEMENTS_EACH_CHAN*PCIE_EDMA_MAX_CHANNELS*PCIE_EDMA_FIFO_ELE_CNT)
#else
#define PCIE_EDMA_WRITE_CHAN_MAX_ELEMENTS (PCIE_EDMA_WRITE_BUSRT_COUNT*PCIE_EDMA_ELEMENTS_EACH_BUFF + 1)
#define PCIE_EDMA_READ_CHAN_MAX_ELEMENTS  (PCIE_EDMA_READ_BUSRT_COUNT*PCIE_EDMA_ELEMENTS_EACH_BUFF + 1)
#endif

typedef enum _PCIE_H2D_MESSAGE_TYPE_
{
    PCIE_H2D_MESSAGE_HOST_READY = 17,/*??0~16 ??????BUS????*/
    PCIE_H2D_MESSAGE_CHIP_TEST_OUTBOUND = 18
}PCIE_H2D_MESSAGE_TYPE;

typedef enum _PCIE_D2H_MESSAGE_TYPE_
{
    PCIE_D2H_MESSAGE_HOST_READY_ACK = 17,/*??0~16 ??????BUS????*/
}PCIE_D2H_MESSAGE_TYPE;

typedef enum _PCIE_SHARED_DEVICE_ADDR_TYPE_
{
    PCIE_SHARED_ADDR_SCHED_CNT = 0,/*control pcie sched mips*/
    PCIE_SHARED_TX_SCHED_CNT = 1,
    PCIE_SHARED_SOFT_FIFO_ENABLE = 2,
    PCIE_SHARED_SOFT_DMA_CHECK = 3,
    PCIE_SHARED_ADDR_BUTT = 16
}PCIE_SHARED_DEVICE_ADDR_TYPE;

typedef enum _PCIE_COMM_RINGBUF_TYPE_
{
    PCIE_COMM_RINGBUF_DMA_WRITE_FIFO = 4,
    PCIE_COMM_RINGBUF_DMA_READ_FIFO,
    PCIE_COMM_RINGBUF_BUTT
}PCIE_COMM_RINGBUF_TYPE;

/*Ring Buff*/
typedef union _edma_paddr_t_{
    struct {
        oal_uint32 low_addr;
        oal_uint32 high_addr;
    }bits;
    oal_uint64 addr;
} edma_paddr_t;

typedef enum _PCIE_H2D_RINGBUF_QTYPE_
{
    PCIE_H2D_QTYPE_HIGH = 0,/*????DEVICE ????????????????????5????????????*/
    PCIE_H2D_QTYPE_NORMAL = 1,/*??????????????????*/
    PCIE_H2D_QTYPE_BUTT
}PCIE_H2D_RINGBUF_QTYPE;

/*Ring-Buff*/
typedef struct _pcie_ringbuf_
{
    /*32??????CPU cache line(32????????32??????64????????64??????????????????)*/
    /*??????????????????????????????*/
	oal_uint32         idx;       /* ring id, used for future*/
	oal_uint32         reserv0;   /* reserv0*/
	oal_uint32         rd;        /* ??????, ??????*/
	oal_uint32         wr;        /* ??????,??????*/
	oal_uint32         size;      /* maximum number of items in ring */
	oal_uint16         item_len;  /* length of each item in the ring */
	oal_uint16         item_mask;  /* item_len ??2??N??????????*/
	oal_uint64         base_addr; /* ????64 bit??????device ????32bit*/
}pcie_ringbuf;

/*16 Bytes*/
typedef struct _pcie_write_ringbuf_item_
{
//    oal_uint32      buf_len;
//    oal_uint32      reserved0;
    edma_paddr_t    buff_paddr;/*rc's ddr address(64 bit)*/
}pcie_write_ringbuf_item;

typedef struct _pcie_read_ringbuf_item_
{
    oal_uint32      buf_len;
    oal_uint32      reserved0;
    edma_paddr_t    buff_paddr;/*rc's ddr address(64 bit)*/
}pcie_read_ringbuf_item;

#define PCIE_H2D_MESSAGE_MAX_ELEMENTS   (32)
#define PCIE_H2D_MESSAGE_ELEMENT_SIZE   (4)

#define PCIE_D2H_MESSAGE_MAX_ELEMENTS   (32)
#define PCIE_D2H_MESSAGE_ELEMENT_SIZE   (4)

typedef struct _pcie_ringbuf_res_
{
    pcie_ringbuf st_d2h_buf;/*write buff*/
    pcie_ringbuf st_h2d_buf[PCIE_H2D_QTYPE_BUTT];/*read buff*/
    pcie_ringbuf st_d2h_msg;/*dev wakeup host gpio trigger*/
    pcie_ringbuf st_h2d_msg;/*host2dev pcie reg triigger*/
    pcie_ringbuf st_ringbuf[PCIE_COMM_RINGBUF_BUTT];
}pcie_ringbuf_res;

typedef struct _pcie_dma_write_fifo_item_
{
    oal_uint32 address;/*Just low 32 bits,used for check*/
    oal_uint16 isr_count;
    oal_uint8  count[PCIE_EDMA_MAX_CHANNELS];/*chan0 & chan1*/
}pcie_dma_write_fifo_item;

typedef struct _pcie_dma_read_fifo_item_
{
    oal_uint16 address;/*Just low 16 bits,used for check*/
    oal_uint16 qid;/*qid*/
    oal_uint16 isr_count;
    oal_uint8  count[PCIE_EDMA_MAX_CHANNELS];/*chan0 & chan1*/
}pcie_dma_read_fifo_item;

typedef struct _pcie_h2d_errors_
{
	oal_uint8 ringbuf_underflow_count;/*Ringbuf????,????????*/
	oal_uint8 get_fifo_worklist_failed;/*????????????????????????????????????*/
	oal_uint8 count_reg_error;/*count????????????*/
	oal_uint8 invaild_fifo_value;/*??????????????FIFO????*/
	oal_uint8 fifo_empty_error;/*??????????????*/
	oal_uint8 reserved[3];
	PCIE_TX_ABORT_STATUS abort_status;
}pcie_h2d_errors;

/*edma read ????????*/
typedef struct _pcie_h2d_stat_
{
    oal_uint32 push_fifo_count;/*??fifo????*/
	oal_uint32 done_isr_count;/*??????????????*/
	oal_uint32 doorbell_isr_count;/*??????????????*/
	oal_uint32 trans_count;/*??????????????*/
	oal_uint32 rx_count;/*????????netbuf????*/
	oal_uint32 rx_queue_count[PCIE_H2D_QTYPE_BUTT];

    oal_uint32 ringbuf_miss;
    oal_uint32 ringbuf_hit;
    oal_uint32 netbuf_miss;
    oal_uint32 netbuf_hit;
    oal_uint32 fifo_full;
    oal_uint32 fifo_notfull;
    oal_uint32 fifo_ele_empty;
    oal_uint32 soft_fifo_busy;

    oal_uint32 pm_busy_cnt;
}pcie_h2d_stat;

typedef struct _pcie_h2d_stats_
{
	pcie_h2d_stat   stat;
    pcie_h2d_errors errors;
}pcie_h2d_stats;

/*edma write ????????*/
typedef struct _pcie_d2h_stat_
{
    oal_uint32 push_fifo_count;/*??fifo????*/
	oal_uint32 done_isr_count;/*??????????????*/
	oal_uint32 doorbell_isr_count;/*??????????????*/
	oal_uint32 trans_count;/*????????????????*/
	oal_uint32 tx_count;/*????????netbuf????*/

    oal_uint32 ringbuf_miss;
    oal_uint32 ringbuf_hit;
    oal_uint32 fifo_full;
    oal_uint32 fifo_notfull;
    oal_uint32 fifo_ele_empty;
    oal_uint32 fifo_dma_idle;
    oal_uint32 fifo_dma_busy;
    oal_uint32 soft_fifo_busy;

    oal_uint32 pm_busy_cnt;
}pcie_d2h_stat;

/*edma write ????????*/
typedef struct _pcie_d2h_errors_
{
	oal_uint8 get_fifo_worklist_failed;/*????????????????????????????????????*/
	oal_uint8 count_reg_error;/*count????????????*/
	oal_uint8 invaild_fifo_value;/*??????????????FIFO????*/
	oal_uint8 reserved;
	PCIE_RX_ABORT_STATUS abort_status;
}pcie_d2h_errors;

typedef struct _pcie_d2h_stats_
{
	pcie_d2h_stat	stat;
    pcie_d2h_errors errors;
}pcie_d2h_stats;

typedef struct _pcie_stat_
{
	oal_int32  inited;/*init flag, ??0??????????0???????????? ????????*/
	oal_uint32 rst_cnt;/*total reset count*/
	oal_uint32 l3_isr_count;/*L3 ????????????*/
	oal_uint32 msg_isr_count;/*????????????????*/
	oal_uint32 h2d_isr_count;/*H2D????????????*/
	oal_uint32 link_down_count;/*PCIE????????*/
	oal_uint32 pm_gpio_sleep_cnt;/*gpio low cnt*/
	oal_uint32 pm_gpio_wakeup_cnt;/*gpio high cnt*/
    oal_uint32 isr_per_max_cnt;/*??????????????????????????????*/
    oal_uint32 msg_fifo_busy_cnt;
}pcie_stat;

typedef struct _pcie_stats_
{
	pcie_stat 	   comm_stat;
	pcie_h2d_stats h2d_stats;
	pcie_d2h_stats d2h_stats;
}pcie_stats;

/*pcie rc/ep shared mem stru*/
typedef struct _pcie_share_mem_stru_
{
    oal_uint32     ringbuf_res_paddr;
    oal_uint32     write_llt_paddr;/*llt address*/
    oal_uint32     read_llt_paddr;
#ifdef _PRE_PLAT_FEATURE_PCIE_DEVICE_STAT
    oal_uint32     device_stat_paddr;
#endif
#ifdef _PRE_PLAT_FEATURE_PCIE_EDMA_ORI
    oal_uint32     write_chan_cnt_addr;
    oal_uint32     read_chan_cnt_addr;
#endif
    oal_uint32     device_addr[PCIE_SHARED_ADDR_BUTT];
}pcie_share_mem_stru;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


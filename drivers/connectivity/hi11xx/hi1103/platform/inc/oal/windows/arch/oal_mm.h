

#ifndef __OAL_WINDOWS_MM_H__
#define __OAL_WINDOWS_MM_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include <windows.h>

/*****************************************************************************
  2 ??????
*****************************************************************************/


/*****************************************************************************
  3 ????????
*****************************************************************************/


/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/

OAL_INLINE oal_void* oal_memalloc(oal_uint32 ul_size)
{
    oal_void *p_mem_space;

    p_mem_space = malloc(ul_size);


    return p_mem_space;
}


OAL_STATIC OAL_INLINE oal_void* oal_memtry_alloc(oal_uint32 request_maxsize, oal_uint32 request_minsize, oal_uint32* actual_size)
{
    oal_void   *puc_mem_space;
    oal_uint32  request_size;

    if(NULL == actual_size)
    {
        return NULL;
    }

    *actual_size = 0;

    request_size = (request_maxsize > request_minsize) ? request_maxsize : request_minsize;

    do
    {
        puc_mem_space = oal_memalloc(request_size);
        if(NULL != puc_mem_space)
        {
            *actual_size = request_size;
            return puc_mem_space;
        }

        if(request_size <= request_minsize)
        {
            /*??????SIZE????????????????NULL*/
            break;
        }

        /*????????, ????????????*/
        request_size = request_size >> 1;
        request_size = (request_size > request_minsize) ? request_size : request_minsize;
    }while(1);

    return NULL;
}


OAL_INLINE oal_void  oal_free(oal_void *p_buf)
{
    free(p_buf);
}


OAL_STATIC OAL_INLINE oal_void* oal_mem_dma_blockalloc(oal_uint32 size, oal_ulong timeout)
{
    OAL_REFERENCE(timeout);
    return oal_memalloc(size);
}


OAL_STATIC OAL_INLINE oal_void  oal_mem_dma_blockfree(oal_void* puc_mem_space)
{
    oal_free(puc_mem_space);
}


OAL_INLINE oal_void  oal_memcopy(oal_void *p_dst, const oal_void *p_src, oal_uint32 ul_size)
{
    memcpy(p_dst, p_src, ul_size);
}


OAL_INLINE oal_void  oal_memmove(oal_void *p_dst, const oal_void *p_src, oal_uint32 ul_size)
{
    memmove(p_dst, p_src, ul_size);
}


OAL_INLINE oal_void  oal_memset(oal_void *p_buf, oal_int32 l_data, oal_uint32 ul_size)
{
    memset(p_buf, l_data, ul_size);
}

#endif /* end of oal_mm.h */


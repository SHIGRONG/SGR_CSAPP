void* next_blkp(void *bp)//查找下一块，如果下一块是结尾块则跳转到开头
{
    bp = NEXT_BLKP(bp)
    if (GET_SIZE(HDRP(bp) == 0)
    {
        bp = heap_listp;
    }
        
        return bp;
}

static void* next_fit(size_t asize)
{
    void * bp = next_listp;//next_listp是上一次搜索的位置
    
    if(!GET_ALLOC(HDRP(bp)) && GET_SIZE(HDRP(bp)) >= asize)
    {
        return bp;
    }
    
    bp = next_blkp(bp);
    while (bp != next_listp)
    {
        if(!GET_ALLOC(HDRP(bp)) && GET_SIZE(HDRP(bp)) >= asize)
        {
            next_listp = bp;
            return bp;
        }
        bp = next_blkp(bp);
    }
    
    return NULL;
}

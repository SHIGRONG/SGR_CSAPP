static void place(void *bp,size_t asize)
{
    size_t size = GET_SIZE(HDRP(bp));
    
    if(size - asize >= 16)
    {
        PUT(HDRP(bp),PACK(asize,1));
        //PUT(FTRP(bp),PACK(asize,1));
        bp = NEXT_BLKP(bp);
        bp = (char *)bp - WSIZE;//因为少了尾部 所有减少WSIZE
        
        PUT(HDRP(bp),PACK(size - asize,2));//对头部的倒数第二位进行标记，表明前面已分配
        PUT(FTRP(bp),PACK(size - asize,1));
    }else
    {
        PUT(HDRP(bp),PACK(size,1));
        //PUT(FTRP(bp),PACK(size,1));
        PUT(HDRP(NEXT_BLKP(bp)),HDRP(NEXT_BLKP(bp))|2);
    }
}


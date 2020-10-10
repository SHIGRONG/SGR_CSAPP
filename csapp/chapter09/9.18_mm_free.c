void mm_free(void *bp)
{
    size_t size = GET_SIZE(HDRP(bp));
    
    PUT(HDRP(bp),GET(FTRP(bp))& ~1);//除了将分配位改变，其他标记不变
    PUT(FTRP(bp)-WSIZE,PACK(size,0));
    PUT(FTRP(bp),GET(FTRP(bp))& ~2);//告诉后面的块，前驱是空闲
    coalesce(bp);
}


static void *coalesce(void *bp)
{
    size_t pre_alloc = (GET(FTRP(bp))>>1)&1;
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));
    
    if(pre_alloc && next_alloc)
        return bp;
    else if(pre_alloc && !next_alloc)
    {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp),GET(HDRP(bp))&7|size);
        PUT(FTRP(bp),PACK(size,0));
    }
    
    else if(!pre_alloc && next_alloc)
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp),PACK(size,0));
        PUT(HDRP(PREV_BLKP(bp)),GET(HDRP(PREV_BLKP(bp)))&7|size);
        bp = PREV_BLKP(bp);
    }
    else
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(FTRP(NEXT_BLKP(bp)),PACK(size,0));
        PUT(HDRP(PREV_BLKP(bp)),GET(HDRP(PREV_BLKP(bp)))&7|size);
        bp = PREV_BLKP(bp);
        
    }
    
    return bp;
}

static void place(void *bp,size_t asize)
{
    size_t size = GET_SIZE(HDRP(bp));
    
    if(size - asize >= 16)
    {
        PUT(HDRP(bp),PACK(asize,1));
        PUT(FTRP(bp),PACK(asize,1));
        bp = NEXT_BLKP(bp);
        
        PUT(HDRP(bp),PACK(size - asize,0));
        PUT(FTRP(bp),PACK(size - asize,0));
    }else
    {
        PUT(HDRP(bp),PACK(size,1));
        PUT(FTRP(bp),PACK(size,1));
    }
}

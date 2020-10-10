static void * find_fit(size_t asize)
{
    void * bp = heap_listp;
    while (GET_SIZE(HDRP(bp)) > 0)
    {
        if (GET_SIZE(HDRP(bp)) >= asize && (!GET_ALLOC(HDRP(bp))))
        {
            return bp;
        }
        
        bp = NEXT_BLKP(bp);
    }
    
    return NULL;
}

void * mm_malloc(size_t size)
{
    int asize;
    int extendsize;
    
    if(size == 0)
        return NULL;
    if(size <= WSIZE)
        asize = DSIZE;
    else{
        asize = DSIZE*((size+(WSIZE)+(DSIZE-1))/DSIZE);
    }
    
    if((bp = find_fit(asize)) != NULL)
    {
        place(bp,asize);
        return bp;
    }
    
    extendsize = MAX(asize,CHUNKSIZE);
    if (bp = extend_heap(extendsize/WSIZE) == NULL) {
        return NULL;
    }
    place(bp,asize);
    return bp;
}

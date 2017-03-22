unsigned char *asctochs (unsigned char* ascii)
{
    int len = strlen ( ascii ) ;
    unsigned char *chs = NULL ;
    int  i = 0 ;
    unsigned char ch[2] = {0};
    if( len%2 != 0 )
    {
        return NULL ;
    }
    chs = (unsigned char*)malloc( len / 2 + 1);                /*malloc chs*/

    while( i < len )
    {
        ch[0] = ( (int)ascii[i] > 64 ) ? ( ascii[i]%16 + 9 ) : ascii[i]%16 ;
        ch[1] = ( (int)ascii[i + 1] > 64 ) ? ( ascii[i + 1]%16 + 9 ) : ascii[i + 1]%16 ;

        chs[i/2] = (unsigned char)( ch[0]*16 + ch[1] );
        i += 2;
    }

    return chs ;            /*chs ∑µªÿ«∞Œ¥ Õ∑≈*/
}

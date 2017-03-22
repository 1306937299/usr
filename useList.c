
int checkCPUendian()
{
    union
    {
        unsigned long int i;
        unsigned char s[4];
    }c;

    c.i = 0x12345678;
    return (0x12 == c.s[0]);
}


/*ģ��ntohll�����������ֽ���ת�����ֽ���*/
uint64_t t_ntohll(uint64_t val)
{
    if (0 == checkCPUendian())
    {
        return (((uint64_t)htonl((int)((val << 32) >> 32))) << 32) | ((unsigned int)htonl((int)(val >> 32)));
    }
    return val;
}

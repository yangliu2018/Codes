void main()
{
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';
    *(video_memory+2) = 'Y';
    char msg[] = "Hello, world!";
    char* p = video_memory;
    char* q = msg;
    while (*q != '\0')
    {
        *p = *q;
        p += 2;
        q += 1;
    }
}

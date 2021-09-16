//Kanellaki Maria Anna - 1115201400060


#include <stdio.h>

int main()
{
    int ch, codepoint, i;
    int count1 = 0, countMulti = 0;


    while ((ch = getchar()) != EOF)
    {
        if ((ch & 0x80) == 0)                                                       //1 byte
        {
            codepoint = ch;
            count1++;
        }

        else if ((ch & 0xE0) == 0xC0)                                               //2 bytes
        {
            codepoint = ch & 0x1F;

            if ((ch = getchar()) == EOF)
            {
                printf("Error. Unexpected EOF.\n");
                return -1;
            }
            if ((ch & 0xC0) != 0x80)
            {
                printf("Invalid UTF-8 tail byte: 0x%02X \n", ch);
                return -2;
            }
            codepoint <<= 6;
            codepoint += (ch & 0x3F);

            if(codepoint < 0x80)
            {
                printf("Oversized UTF-8 code point: U+%02X\n", codepoint);
                return -5;
            }

            countMulti++;
        }

        else if ((ch & 0xF0) == 0xE0)                                               //3 bytes
        {
            codepoint = ch & 0x0F;

            for (i = 0; i < 2; i++)                                                 //2 tail bytes
            {
                if ((ch = getchar()) == EOF)
                {
                    printf("Error. Unexpected EOF.\n");
                    return -1;
                }
                if ((ch & 0xC0) != 0x80)
                {
                    printf("Invalid UTF-8 tail byte: 0x%02X \n", ch);
                    return -2;
                }

                codepoint <<= 6;
                codepoint += (ch & 0x3F);
            }

            if (codepoint >= (0xD800)  && codepoint <= 0xDFFF)
            {
                printf("Invalid UTF-8 code point: U+%02X\n", codepoint);
                return -4;
            }
            if(codepoint < 0x800)
            {
                printf("Oversized UTF-8 code point: U+%02X\n", codepoint);
                return -5;
            }

            countMulti++;
        }

        else if ((ch & 0xF8) == 0xF0)                                               //4 bytes
        {
            codepoint = ch & 0x07;

            for (i = 0; i < 3; i++)						    //3 tail bytes
            {
                if ((ch = getchar()) == EOF)
                {
                    printf("Error. Unexpected EOF.\n");
                    return -1;
                }
                if ((ch & 0xC0) != 0x80)
                {
                    printf("Invalid UTF-8 tail byte: 0x%02X \n", ch);
                    return -2;
                }

                codepoint <<= 6;
                codepoint += (ch & 0x3F);
            }

            if (codepoint > 0x10FFFF)
            {
                printf("Invalid UTF-8 code point: U+%02X\n", codepoint);
                return -4;
            }
            if(codepoint < 0x10000)
            {
                printf("Oversized UTF-8 code point: U+%02X\n", codepoint);
                return -5;
            }

            countMulti++;
        }
        else
        {
            printf ("Invalid UTF-8 header byte: 0x%02X\n", ch);
            return -3;
        }

        //printf ("U+%04X\n", codepoint);
    }

    printf ("Found %d ASCII and %d multi-byte UTF-8 characters.\n", count1, countMulti);
    return 0;
}


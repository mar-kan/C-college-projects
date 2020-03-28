#include <stdio.h>

int main(void)
{
	int ch, cp, i, count1, count2 ;

	count1 = 0 ;
	count2 = 0 ;
	
	while((ch = getchar()) != EOF)
	{
		
		if((ch & 0x80)==0)
		{
			cp = ch ;
			count1++ ;							
		}
		else if((ch & 0xE0)==0xC0)
		{
			 	cp = ch & 0x1F ;
			 		if((ch = getchar())== EOF)
					{
					 	printf("Unexpected EOF\n") ;
					 	return 1 ;
					}
					if((ch & 0xC0) != 0x80)
					{
						printf("Invalid tail byte: 0x%02X\n",ch) ;
						return 2 ;
					}
					
				cp <<= 6 ;
				cp += (ch & 0x3F) ;
				
					if(cp<=0x0080)
					{
						printf("Oversized UTF-8 Codepoint: 0x%02X\n",cp) ;
						return 4 ;
					}
					
				count2++ ;
		}
		
		else if((ch & 0xF0 )== 0xE0)
		{
				cp = ch & 0x0F ;
				
				for(i=0;i<2;i++)
				{
					if((ch = getchar())== EOF)
					{
						printf("Unexpected EOF \n") ;
						return 1 ;
					}
					if((ch & 0xC0)!= 0x80) 
					{
						printf("Invalid tail byte: 0x%02X\n", ch) ;
						return 2 ;
					}
									
					cp <<= 6 ;
					cp += (ch & 0x3F ) ;
				}

					if ((cp>=0xD800) && (cp<=0xDFFF))
					{
						printf("Invalid UTF-8 Codepoint: 0x%02X\n", cp) ;
						return 3 ; 
					}

					if(cp<=0x0800)
					{
						printf("Oversized UTF-8 Codepoint: 0x%02X\n",cp) ;
						return 4 ;
					}
					
				count2++ ;
		}	
		else if((ch & 0xF8)==0xF0)
		{
				cp = ch & 0x0F ;
				
				for(i=0;i<3;i++)
				{
					if((ch = getchar())== EOF)
					{
						printf("Unexpected EOF \n") ;
						return 1 ;
					}
					if((ch & 0xC0)!=0x80)
					{
						printf("Invalid tail byte: 0x%02X\n", ch) ;
						return 2 ;
					}
									
					cp <<= 6 ;
					cp += (ch & 0x3F ) ;
				}

					if (cp>0x10FFFF)
					{
						printf("Invalid UTF-8 Codepoint: 0x%02X\n", cp) ;
						return 3 ; 
					}
					
					if(cp<=0x010000)
					{
						printf("Oversized UTF-8 Codepoint: 0x%02X\n",cp) ;
						return 4 ;
					}
								
				count2++ ;
		}
		else
		{
			printf("Invalid UTF-8 header byte: %02X\n", ch) ;
			return 5 ;
		}
														//		printf("U+%04X\n", cp) ;											
	}
	
	printf("Found %d ASCII and %d Multi-Byte UTF-8 characters. \n", count1, count2) ;
	return 0 ;
}

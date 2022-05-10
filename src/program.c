#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"

int main(int argc, char **argv)
{
	IS is, is2;
	Dllist l,tmp;
	int i,j;
	
	if	(argc != 4 || strcmp(argv[0],"bin/ceviri") || 
		(strcmp(argv[1],"tr") && strcmp(argv[1],"eng")) || 
		strcmp(argv[2],"txt/input.txt") || strcmp(argv[3],"txt/sozluk.txt")
		)
	{
		fprintf(stderr, "usage: bin/ceviri {eng/tr} txt/input.txt txt/sozluk.txt\n");
		exit(1);
	}
	
	is = new_inputstruct(argv[2]);
	l = new_dllist();
	
	if(is == NULL)
	{
		perror(argv[2]);
		exit(1);
	}
	
	int comparedWordCount = 0;
	int translatedWordCount = 0;
	
	if(!strcmp(argv[1],"eng"))
	{
    	while(get_line(is) >= 0) 
		{
    		for(i = 0; i < is->NF; i++) 
    		{
    			dll_append(l, new_jval_s(strdup(is->fields[i])));
    			comparedWordCount++; 
    			is2 = new_inputstruct(argv[3]);
    			while(get_line(is2) >= 0) 
				{
    				if(!strcmp(is->fields[i],is2->fields[2]))
    				{
    					dll_delete_node(l->blink);
    					dll_append(l, new_jval_s(strdup(is2->fields[1])));
    					translatedWordCount++;
    					break;
    				}
    			}
    			jettison_inputstruct(is2);
    		}
    	}
	}
	else if(!strcmp(argv[1],"tr"))
	{
		while(get_line(is) >= 0) 
		{
    		for(i = 0; i < is->NF; i++) 
    		{
    			dll_append(l, new_jval_s(strdup(is->fields[i])));
    			comparedWordCount++; 
    			is2 = new_inputstruct(argv[3]);
    			while(get_line(is2) >= 0) 
				{
    				if(!strcmp(is->fields[i],is2->fields[1]))
    				{
    					dll_delete_node(l->blink);
    					dll_append(l, new_jval_s(strdup(is2->fields[2])));
    					translatedWordCount++;
    					break;
    				}
    			}
    			jettison_inputstruct(is2);
    		}
    	}
	}
	
	is->f = fopen("txt/output.txt", "w");
    
    tmp = l->flink;
  	while(tmp != l) 
  	{
  		fprintf(is->f, "%s ", tmp->val.s);
    	tmp = tmp->flink;
  	}
  	
  	printf("Ozet Bilgi:\n");
  	printf("Karsilastirilan kelime sayisi:%d\n",comparedWordCount);
  	printf("Cevirisi basarili kelime sayisi:%d\n",translatedWordCount);
  	printf("Cevirisi yapilamamis kelime sayisi:%d\n",comparedWordCount-translatedWordCount);
	
	jettison_inputstruct(is);
	
	return 0;
}

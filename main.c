#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct head {
	unsigned char type;
	unsigned int len;
} head;

typedef struct data_structure {
	head *header;
	void *data;
} data_structure;

int add_last(void **arr, int *len, data_structure *data)
{
	if(*arr==NULL){		//daca vectorul este gol
		*arr = calloc(data->header->len + sizeof(char) + sizeof(int), 1);	//se aloca pt type, len si lungimea datelor
		if(!*arr) return 0;
		memcpy(*arr, &data->header->type, sizeof(char));   //se copiaza in vector pe rand, type ul si len ul din header
		memcpy(*arr + sizeof(char), &data->header->len, sizeof(int));	//pentru a rezolva problematica de padding
		memcpy(*arr + sizeof(char) + sizeof(int), data->data, data->header->len);	//apoi se copiaza datele
		(*len) ++;	//se actualizeaza numarul de elemente din vector
	}
	else {
		int poz = 0;
		poz = *(int*)((char*)(*arr+1))+ sizeof(char) + sizeof(int);		//lungimea primului element din vector
		for(int i = 2; i<= *len; i++)
		{	
			poz += *(int*)((char*)(*arr+poz+1)) + sizeof(int) + sizeof(char);//in poz se calculeaza lungimea vectorului
		}
		*arr = realloc((*arr), data->header->len + sizeof(char) + sizeof(int)+ poz); //realocarea mem. pt noul element
		memcpy(*arr+ poz, &data->header->type, sizeof(char));	//se repeta procedeul de mai sus, copierea fiind
		memcpy(*arr + poz + sizeof(char), &data->header->len, sizeof(int)); //la adresa lui arr+lungimea sa
		memcpy(*arr + sizeof(char) + sizeof(int) + poz, data->data, data->header->len);
		(*len)++;
		
	}
	return 1;
}

void print(void *arr, int len){

	char tip;
	for(int i = 0; i<len; i++){ //se parcurg toate elementele vectorului

		tip = *(char*)arr;	//variabila unde se stocheaza tipul
		if (tip == '1'){
			int8_t b1, b2;
			printf("Tipul %c\n", *(char*)arr);
			printf("%s pentru ", (char*)(arr + sizeof(int) + sizeof(char))); //primul cuv este dupa elem. headerului
			int poz = strlen((char*)(arr + sizeof(int) + sizeof(char)))+sizeof(int) + sizeof(char); 
			arr = arr + poz + 1;	//poz = dimensiunea primului string + dimensiunea elementelor din header
			b1 = *(int8_t*)arr;	//se converteste la tipul dorit
			arr = arr + sizeof(int8_t);	//se trece la zona de memorie urmatoare
			b2 = *(int8_t*)arr;
			arr = arr + sizeof(int8_t);
			printf("%s\n", (char*)arr);
			char *s =(char*)arr;
			arr = arr + strlen(s) + 1;
			printf("%"PRId8"\n", b1);
			printf("%"PRId8"\n", b2);
			printf("\n");
		}
		else if (tip == '2'){
			int16_t b1;
			int32_t b2;
			printf("Tipul %c\n", *(char*)arr);
			printf("%s pentru ", (char*)(arr + sizeof(int) + sizeof(char) ));
			int poz = strlen((char*)(arr + sizeof(int) + sizeof(char)))+sizeof(int) + sizeof(char);
			arr = arr + poz+1;
			b1 = *(int16_t*)arr;
			arr = arr + sizeof(int16_t);
			b2 = *(int32_t*)arr;
			arr = arr + sizeof(int32_t);
			printf("%s\n", (char*)arr);
			char *s =(char*)arr;
			arr = arr + strlen(s) + 1;
			printf("%"PRId16"\n", b1);
			printf("%"PRId32"\n", b2);
			printf("\n");
		}
		else {
			int32_t b1;
			int32_t b2;
			printf("Tipul %c\n", *(char*)arr);
			printf("%s pentru ", (char*)(arr + sizeof(int) + sizeof(char) ));
			int poz = strlen((char*)(arr + sizeof(int) + sizeof(char))) + sizeof(int) + sizeof(char);
			arr = arr + poz+1;
			b1 = *(int32_t*)arr;
			arr = arr + sizeof(int32_t);
			b2 = *(int32_t*)arr;
			arr = arr + sizeof(int32_t);
			printf("%s\n", (char*)arr);
			char *s =(char*)arr;
			arr = arr + strlen(s) + 1;
			printf("%"PRId32"\n", b1);
			printf("%"PRId32"\n", b2);
			printf("\n");

		}
		
	}
}

	


int add_at(void **arr, int *len, data_structure *data, int index)
{
	if (index < 0)	return -1; //intoarce o eroare
	else if(index > *len) return add_last(arr, len, data);
	else
	{	
		int poz = 0;
		int poz2 = 0;
		for(int i = 0; i< *len; i++)	//se calc. lungimea vectorului pt realocare
		{								//si lungimea elementelor pana la indexul primit
			if(i < index ) poz2+= *(int*)((char*)(*arr+poz+1)) + sizeof(int) + sizeof(char);
			poz += *(int*)((char*)(*arr+poz+1)) + sizeof(int) + sizeof(char);

		}
		*arr = realloc((*arr), data->header->len + sizeof(char) + sizeof(int)+ poz );
		memcpy(*arr +poz2 +sizeof(char) +sizeof(int) +data->header->len, *arr +poz2, poz -poz2 ); //se muta elementele
		memcpy(*arr +poz2, &data->header->type, sizeof(char));								//de dupa index la dreapta
		memcpy(*arr +poz2 +sizeof(char), &data->header->len, sizeof(int));					//si se adauga elementul
		memcpy(*arr +poz2 +sizeof(char) +sizeof(int), data->data, data->header->len);			//pe pozitia indexului
		}

	(*len)++;
	return 1;
	
}

void find(void *data_block, int len, int index) 
{
	if(index < len && index >= 0 ){
		int poz = 0;
		for(int i = 0; i< index; i++)	//lungimea vectorului pana la elementul cerut
		{	
			poz += *(int*)((char*)(data_block+poz+1)) + sizeof(int) + sizeof(char);
		}
		print((char*)(data_block+poz), 1);	//se apeleaza functia de printare pt un singur element, incepand
	}													//de la adresa elemntului cautat

}

int delete_at(void **arr, int *len, int index)
{
	int poz = 0, size, poz2=0;
	for(int i = 0; i< *len; i++)	//se calc lungimea vectorului totala si cea pana la elementul dat
		{	
			if(i < index ) poz2+= *(int*)((char*)(*arr + poz + 1)) + sizeof(int) + sizeof(char);
			poz += *(int*)((char*)(*arr + poz + 1)) + sizeof(int) + sizeof(char);

		}
	size = *(int*)((char*)(*arr + poz2 + 1));	//lungimea elemntului urmator fata de cel dat
	//se muta spre dreapta elementele de dupa cel dat, cu o lungime = lungimea elementului de eliminat
	memcpy(*arr + poz2, *arr + poz2 + size + sizeof(int) + sizeof(char), poz -poz2 -sizeof(char) -sizeof(int) -size);
	*arr = realloc((*arr), poz-size-sizeof(int)-sizeof(char));	//se realoca memorie, scazandu-se dim. elementului dat
	(*len)--;
	return 1;
	

}
//convertTip1/2/3 sparge linia p in cuvinte si pune intr-o data_structure elementele specifice tipului
data_structure* convertTip1( char* p , data_structure* ds){

	char *spatiu = malloc(1);
	*spatiu = '\0';
	int8_t b1;
	int8_t b2;
	p = strtok(NULL, " ");
	ds->header->len = strlen(p)+1;	//lungimea cuvantului + caracterul null
	ds->data = malloc(ds->header->len);	//aloca memorie pt date
	memcpy(ds->data, p, ds->header->len-1);	//pune primul cuvant
	memcpy(ds->data + ds->header->len - 1, spatiu, 1); //pune null la finalul lui
	p = strtok(NULL, " ");
	ds->data = realloc(ds->data, 2*sizeof(int8_t)+ds->header->len); //realoca mem si pt cele 2 int8_t uri
	b1 = atoi(p);	//converteste stringul in numar
	memcpy(ds->data + ds->header->len, &b1, sizeof(int8_t));	//copiaza primul nr
	ds->header->len += sizeof(int8_t);	//actualizeaza lungimea
	p = strtok(NULL, " ");
	b2 = atoi(p);
	memcpy(ds->data + ds->header->len, &b2, sizeof(int8_t));	//in continuarea memoriei, il pune pe al doilea
	ds->header->len += sizeof(int8_t);
	p = strtok(NULL, " ");
	ds->data = realloc(ds->data, ds->header->len + strlen(p)+1);
	memcpy(ds->data + ds->header->len, p, strlen(p));
	ds->header->len+=strlen(p);
	memcpy(ds->data +ds->header->len, spatiu, 1);
	ds->header->len++;
	free(spatiu);
	return ds;	
}
data_structure *convertTip2(char*p, data_structure* ds){

	char *spatiu = malloc(1);
	*spatiu = '\0';
	int16_t b1;
	int32_t b2;
	p = strtok(NULL, " ");
	ds->header->len = strlen(p)+1;
	ds->data = malloc(ds->header->len);
	memcpy(ds->data, p, ds->header->len-1);
	memcpy(ds->data +ds->header->len-1, spatiu, 1);
	p = strtok(NULL, " ");
	ds->data = realloc(ds->data, sizeof(int32_t)+sizeof(int16_t)+ds->header->len);
	b1 = atoi(p);
	memcpy(ds->data + ds->header->len, &b1, sizeof(int16_t));
	ds->header->len += sizeof(int16_t);
	p = strtok(NULL, " ");
	b2 = atoi(p);
	memcpy(ds->data + ds->header->len, &b2, sizeof(int32_t));
	ds->header->len += sizeof(int32_t);
	p = strtok(NULL, " ");
	ds->data = realloc(ds->data, ds->header->len + strlen(p)+1);
	memcpy(ds->data + ds->header->len, p, strlen(p));
	ds->header->len+=strlen(p);
	memcpy(ds->data +ds->header->len, spatiu, 1);
	ds->header->len++;
	free(spatiu);
	return ds;

}

data_structure* convertTip3(char*p, data_structure*ds){

	char *spatiu = malloc(1);
	*spatiu = '\0';
	int32_t b1;
	int32_t b2;
	p = strtok(NULL, " ");
	ds->header->len = strlen(p)+1;
	ds->data = malloc(ds->header->len);
	memcpy(ds->data, p, ds->header->len-1);
	memcpy(ds->data +ds->header->len-1, spatiu, 1);
	p = strtok(NULL, " ");
	ds->data = realloc(ds->data, ds->header->len+ 2*sizeof(int32_t));
	b1 = atoi(p);
	memcpy(ds->data + ds->header->len, &b1, sizeof(int32_t));
	ds->header->len += sizeof(int32_t);
	p = strtok(NULL, " ");
	b2 = atoi(p);
	memcpy(ds->data + ds->header->len, &b2, sizeof(int32_t));
	ds->header->len += sizeof(int32_t);
	p = strtok(NULL, " ");
	ds->data = realloc(ds->data, ds->header->len+ strlen(p)+1);
	memcpy(ds->data + ds->header->len, p, strlen(p));
	ds->header->len+=strlen(p);
	memcpy(ds->data +ds->header->len, spatiu, 1);
	ds->header->len++;
	free(spatiu);
	return ds;

}


int main() {

	void *arr = NULL;
	int len = 0;
	char *cerinta = malloc(256); //max caracterul citite pe linie este de 256
	char *p; //se va sparge in cuvinte
	while(fgets(cerinta, 256, stdin)){
		
		if(strcmp(cerinta, "\n\r")) p = strtok(cerinta, "\n\r");	//elimina newline urile si caracterul de returnare
		p = strtok(cerinta, " ");
		if(strcmp(p, "insert")==0){

			data_structure *ds = calloc(sizeof(data_structure), 1);	//la fiecare element se aloca o data-structure ce
			ds->header = calloc(sizeof(head), 1);					//va fi transmisa functiilor ca parametru
			p = strtok(NULL, " ");
			ds->header->type = p[0];
			if(ds->header->type=='1'){
				
				ds = convertTip1 (p, ds);	//pune intr-o data_structure datele de tip 1
				add_last(&arr, &len, ds);

			}
			else if(ds->header->type=='2'){
				
				ds = convertTip2(p, ds);	//pune intr-o data_structure datele de tip 2
				add_last(&arr, &len, ds);

			}
			else{
				
				ds = convertTip3(p, ds);	//pune intr-o data_structure datele de tip 3
				add_last(&arr, &len, ds);
			}
			free(ds->header);	//sunt copiati bitii, deci se poate elibera memoria pt auxiliare 
			free(ds->data);
			free(ds);
		

		}
		else if (strcmp(p, "print")==0) 	print(arr, len);
		else if (strcmp(p, "insert_at")==0){
			int index;
			p = strtok(NULL, " ");
			index = atoi(p);
			data_structure *ds = calloc(sizeof(data_structure), 1);
			ds->header = calloc(sizeof(head), 1);
			p = strtok(NULL, " ");
			ds->header->type = p[0];
			if(ds->header->type=='1'){
				
				ds = convertTip1 (p, ds);
				add_at(&arr, &len, ds, index);

			}
			else if(ds->header->type=='2'){
				
				ds = convertTip2(p, ds);
				add_at(&arr, &len, ds, index);

			}
			else{
				
				ds = convertTip3(p, ds);
				add_at(&arr, &len, ds, index);
			}
			free(ds->header);
			free(ds->data);
			free(ds);

		}
		else if(strcmp(p, "find")==0){

			p = strtok(NULL," ");
			int index = atoi(p);
			find(arr, len, index);
		}
		else if (strcmp(p, "delete_at")==0) {
			p = strtok(NULL, " ");
			int index = atoi(p);
			delete_at(&arr,&len,index);}
		else {
			free(arr);
			free(cerinta);}
		
	}
	

	return 0;
}

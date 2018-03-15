//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									               	    																								    //
//							||			  ||	||					||      	 ||			 ||	  ||	||||||	 ||   	||					  ||			//
//							 ||			  ||	||				||     ||	     ||			 ||	  ||	||	||	 ||		||	    ||	||	||    ||   		  	//
//				|||||||||||||||			||||	||	         ||||||||||||||||||||||        ||||	  ||	||||||	 ||		||    ||||||||||||||||||			//
//				||	||	||				||		||		     ||		 	   ||	||		   ||	  ||  		||	 ||		||	  || 		   ||				//
//				||				 	  ||		||		    ||				||||		  ||  	  || 		||	 ||		||	  ||							//
//				||					|||			||		 |||							|||		  ||		||||||||||||||	  ||				 			//
//																																							//
//																																							//
//																																							//
//											     	 CODED BY : Muhammad Faris Muzakki 1606923 			   													//
//														    		ILMU KOMPUTER 2016																		//
//																																							//
//                                              Saya Muhammad Faris Muzakki Mengerjakan evaluasi TMD		        										//
//                                     	      dalam matakuliah struktur data untuk keberkahannya maka saya tidak 											//
//										   	   melakukan kecurangan seperti yang telah dispesifikan. Aamiin				 									//
//	                                        																							     				//
//											                                													    						//
//		   											       																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "header.h"

//prosedur pemisah jenis inputan
void pisah(char *input, char *orangtua, char *nama_anak, int *jumlah_kondisi){
	//variabel increment
	int i,j=0,k=0,l=0;
	//variabel tanda jenis inputan
	int status = 0;
	//variabel penampung jumlah kondisi
	char tampung[500];

	//proses cek
	for(i=0; i<strlen(input); i++){
		//kondisi untuk mengcopy bapak
		if(status == 0){
			if(input[i] == '#'){
				status = 1;
				i++;
			//batas akhir string
			orangtua[j] = '\0';
			}else{
				//proses pengcopyan
				orangtua[j] = input[i];
				j++;
			}
		}
		//kondisi untuk mengcopy anak
		if(status == 1){
			if(input[i] == '#'){
				status = 2;
				i++;
				//batas akhir string
				nama_anak[k] = '\0';
			}else{
				//proses pengcopyan
				nama_anak[k] = input[i];
				k++;
			}
		}

		//kondisi untuk mengcopy banyaknya perbuatan yang dilakukan
		if(status == 2){
			tampung[l] = input[i];
			l++;
		}	
		//proses pengcopyan banyak perbuatan yang dilakukan
		if(i == strlen(input)-1){
			(*jumlah_kondisi) = atoi(tampung);
		}
	}
}



//Membuat pohon
void makeTree(char *info, tree *T){
	simpul *node;
	node = (simpul *) malloc(sizeof (simpul));
	strcpy(node->info,info);
	node->level = 1;
	node->sibling = NULL;
	node->child = NULL;
	(*T).root = node;
}

//menambahkann anak
void addChild(char *info, simpul *root,container *isi,int banyak){
	if(root != NULL){
		//jika root tidak kosong
		simpul *node;
		node = (simpul *) malloc (sizeof(simpul));
		strcpy(node->info,info);

		node->child = NULL;
		int i;

		createList_isi(&node->isi);
		//copy isi kebaikan
		for(i=0; i<banyak; i++){
			addLast_isi(isi[i].kebaikan,&(node->isi));
		}

		if(root->child == NULL){
			//simpul baru menjadi anak pertama
			node->sibling = NULL;
			root->child = node;
		}else{
			if(root->child->sibling == NULL){
				//jika simpul baru menjadi anak kedua
				node->sibling = root->child;
				root->child->sibling = node;
			}else{
				simpul *last = root->child;
				//mencari simpul anak terakhir
				while(last->sibling != root->child){
					last = last->sibling;
				}
				
				node->sibling = root->child;
				last->sibling = node;
			}
		}
	}
}

//mencari simpul dari nama yang dicari
simpul* findSimpul(char *info, simpul *root){

	simpul *hasil = NULL;

	if(root != NULL){
		if(strcmp(root->info,info)==0){
			hasil = root;
		}else{
			simpul *node = root->child;
			if(node != NULL){
				if(node->sibling == NULL){
					//jika memiliki satu anak
					if(strcmp(node->info,info)==0){
						hasil = node;
					}else{
						hasil = findSimpul(info,node);
					}
				}else{
					//jika memiliki banyak
					int ketemu = 0;
					while((node->sibling != root->child) && (ketemu == 0) && (hasil == NULL)){
						if(strcmp(node->info,info)==0){
							hasil = node;
							ketemu = 1;
						}else{
							hasil = findSimpul(info, node);//cari di anaknya
							node = node->sibling;//iterasi sibling
						}
					}	
					//memproses simpul anak terakhir karena belum terproses dalam pengulangan
					if((ketemu == 0) && (hasil == NULL)){
						if(strcmp(node->info,info)==0){
							hasil = node;
						}else{
							hasil = findSimpul(info,node);
						}
					}
				}
			}
		}
	}
	return hasil;
}

//print secara preOrder
void printTreePreOrder(simpul *root, elemenList *max){

	if(root != NULL){
		//variabel increment
		int i,j;
		//rpint spasi
		for(i=0; i<max->max_level; i++){
			printf(" ");
		}


		printf("|%s\n",root->info);

		//print isi
		elemenList2 *bantu = root->isi.first;
		while(bantu != NULL){
			for(j=0; j<max->max_level; j++){
				printf(" ");
			}
			printf(" %s\n",bantu->kebaikan);
			bantu = bantu->next;
		}

		//increment
		if(max->next != NULL){
			max = max->next;
		}
		
		simpul *node = root->child;
		if(node != NULL){
			if(node->sibling == NULL){
				//jika memiliki satu anak
				printf("\n");
				printTreePreOrder(node,max);
			}else{
				//jika memiliki banyak anak
				//mencetak simpul anak
				while(node->sibling != root->child){
					printf("\n");
					printTreePreOrder(node,max);
					node = node->sibling;
				}
				//memproses simpul anak terakhir karena belum terproses dalam perulangan
				printf("\n");
				printTreePreOrder(node,max);
			}
		}
	}
}

//copy daun
void copy_daun(simpul *root, list *L, simpul **daun){

	if(root != NULL){
		simpul *node = root->child;
		if(node != NULL){
			if(node->sibling == NULL){
				//jika memiliki satu anak
				copy_daun(node,L,daun);
			}else{
				//jika memiliki banyak anak
				//mencetak simpul anak
				while(node->sibling != root->child){
					copy_daun(node,L,daun);
					node = node->sibling;
				}
				//memproses simpul anak terakhir karena belum terproses dalam perulangan
				copy_daun(node,L,daun);
			}
		}
		//cari kedalaman maximum dari yg dicari
		if((*L).first->max_level < root->level){
			(*L).first->max_level = root->level;
			(*daun) = root;
		}	
	}
}

//mencari daun
void cari_tanda_daun(simpul *root, list *L, simpul **daun){

	if(root != NULL){
		simpul *node = root->child;
		if(node != NULL){
			if(node->sibling == NULL){
				//jika memiliki satu anak
				copy_daun(node,L,daun);
			}else{
				//jika memiliki banyak anak
				//mencetak simpul anak
				while(node->sibling != root->child){
					copy_daun(node,L,daun);
					node = node->sibling;
				}
				//memproses simpul anak terakhir karena belum terproses dalam perulangan
				copy_daun(node,L,daun);
			}
		}
		//cari kedalaman maximum dari yg dicari
		if((*L).first->max_level < root->level){
			(*L).first->max_level = root->level;
			(*daun) = root;
		}	
	}
}


//prosedur print nama yang dicari
void print_nama(char nama[],int status, simpul *root){

	if((root != NULL)){
		simpul *node = root->child;
		if(node != NULL){
			if(node->sibling == NULL){
				//jika memiliki satu anak
				print_nama(nama,status,node);
			}else{
				//jika memiliki banyak anak
				//mencetak simpul anak
				while(node->sibling != root->child){
					print_nama(nama,status,node);
					node = node->sibling;
				}
				//memproses simpul anak terakhir karena belum terproses dalam perulangan
				print_nama(nama,status,node);
			}
		}
		//saat ketemu
		if(strcmp(nama,root->info)==0){
			//jika di panggil untuk print nama
			if(status == 0){
				printf("%s",root->info);	
			}else{
				//jika di panggil untuk print kebaikan
				//variabel increment
				int i;

				//jika yang di print adalah kebaikan dari dan terakhir
				if(status == 2){
					printf("tandanya:\n");
				}
				//proses print
				elemenList2 *bantu = root->isi.first;
				while(bantu != NULL){

					printf("- %s\n",bantu->kebaikan);
					bantu = bantu->next;
				}
			}
		}
	}
}

//print nama nama yang dicari
void cari_nama(int banyak ,char nama[banyak][500], tree T){

	//looping print
	int i;
	for(i=0; i<banyak; i++){

		//untuk print root
		if(i==0){
			//pemanggilan prosedur untuk pencarian + print
			print_nama(nama[i],0,T.root);
			printf(":\n");
		}else{
			// print selain root
			printf("- ");
			print_nama(nama[i],0,T.root);
			printf("\n");
		}
	}
}

//print nama nama yang dicari
void cari_kebaikan(int banyak ,char nama[banyak][500], tree T){

	//looping print
	int i;
	printf("perbuatan yang dilakukan:\n");
	for(i=0; i<banyak; i++){
		//pemanggilan prosedur untuk pencarian + print
		print_nama(nama[i],1,T.root);			
	}
}

//mencari daun
void cari_daun(simpul *root, list *L, simpul **daun){

	//melakukan pencarian kedalaman terdalam dari pencarian
	(*L).first->max_level = 0;

	//dekalarasi awal pointer daun
	*(daun) = NULL;

	//pencarian daun
	cari_tanda_daun(root,L,&(*daun));

	//print sesuai test case
	printf("hal yang didapat:\n");
	printf("- %s\n",(*daun)->info);


}

// hitung kedalaman simpul
//---Algortima DROPDOWN yang ada pada forum N-Ary tree Stack Overflow---//
int cari_Level(simpul *root, char *nama, int level){
	//deklarasi variabel pointer
	simpul *temp = root;
	simpul *increment;

	//incrementiabek kedalaman
	int kendalaman = 0;

	// jika simpulnya kosong, alias pohon belum dibuat
	if (root == NULL){
		return 0;
	}

	// jika tidak memiliki sibling
 	if (root->sibling == NULL){ 
		if (strcmp(root->info,nama) == 0){
			return level;
 	   }
 	   //increment
	    increment = root->child;

		if (increment != NULL) {
			// kedalaman (recursive)
			kendalaman = cari_Level(increment, nama, level+1);
			// jika hasil tidak 0, kemudian lempar hasil
			if (kendalaman != 0){	
	        	return kendalaman;
			}
	    }
	// jika memiliki sibling, cek semua
	}else{ 
    	while (root->sibling != temp) {
	    	if (strcmp(root->info,nama) == 0){
	        	return level;
	    	}

	    	//increment
	    	increment = root->child;

	    	if (increment != NULL) {
	        	kendalaman = cari_Level(increment, nama, level+1);
	        	if (kendalaman != 0){
	          		return kendalaman;
	        	}
	    	}
	    	//increment ke sibling
	    	root = root->sibling;
    	}

    	if (strcmp(root->info, nama) == 0){
      		return level;
    	}
    	//increment
    	increment = root->child;

    	if (increment != NULL) {
      		kendalaman = cari_Level(increment, nama, level+1);
      		if (kendalaman != 0){
        		return kendalaman;
      		}
  		}
  	}

  	// lempar hasil
	return kendalaman; 
}




//mengisi level masing masing simpul
void isi_level(char *nama, tree T){

	//mengisi level 
	simpul *bantu = findSimpul(nama,T.root);
	if(bantu != NULL){
		findSimpul(nama,T.root)->level = cari_Level(T.root, nama, 1);
	}

}

//menentukan kedalaman maximum
void cari_max(char *nama, tree T, list *L){
	//menentukan kedalaman maximum
	if(findSimpul(nama,T.root)){

		if((*L).first->max_level < cari_Level(T.root, nama, 1)){
			(*L).first->max_level = cari_Level(T.root, nama, 1);
		}
	}
}


//memindahkan isi tree ke stack
void pindah_stack(simpul *root, stack *S){

	if(root != NULL){
		//proses pemindahan
		push(root->info,root->level,S);
		int i;

		//copy isi
		elemenList2 *bantu = root->isi.first;
		while(bantu != NULL){
			push(bantu->kebaikan,root->level,S);
			bantu = bantu->next;
		}

		simpul *node = root->child;
		if(node != NULL){
			if(node->sibling == NULL){
				//jika memiliki satu anak
				pindah_stack(node,S);
			}else{
				//jika memiliki banyak anak
				//mencetak simpul anak
				while(node->sibling != root->child){
					pindah_stack(node,S);
					node = node->sibling;
				}
				//memproses simpul anak terakhir karena belum terproses dalam perulangan
				pindah_stack(node,S);
			}
		}
	}
}

//deklarasi pembuatan stack
void createEmpty(stack *S){
	(*S).top = NULL;
}

//mengditung banyaknya isi stack
int countElement(stack S){
	int hasil = 0;

	if(S.top != NULL){
		elemen *elmt;

		//inisiasi
		elmt = S.top;

		while(elmt != NULL){
			//penghitungan
			hasil++; 
			//increment
			elmt = elmt->next;
		}
	}
	return hasil;
}

//isi stack
void push(char nama[],int level, stack *S ){

	elemen *baru;
	baru = (elemen *) malloc (sizeof (elemen));

	strcpy(baru->elmt.kebaikan,nama);
	baru->level = level;

	if((*S).top != NULL){
		baru->next = (*S).top;
	}else{
		baru->next = NULL;
	}
	(*S).top = baru;
	baru = NULL;
}

//delete isi stack
void popAll(stack *S){

	while((*S).top != NULL){
		//jika stack tidak kosong
		elemen *delete = (*S).top;
		(*S).top = (*S).top->next;
		delete->next = NULL;
		free(delete);
	}
}

//print isi elemen
void printStack(stack S){
	if(S.top != NULL){
		//jika list tidak kosong
		//inisiaslisasi
		elemen *bantu = S.top;
		while(bantu != NULL){
			//proses 
			printf("%s %d\n", bantu->elmt.kebaikan,bantu->level);
			//iterasi
			bantu = bantu->next;
		}
	}
	printf("\n");
}

//hitung spasi
void hitung_spasi(stack S, list *L, list *max){

	//proses hitung masing masing level
	int i;
	
	//penampung sementara untuk max spasi
	int spasi[100];
	spasi[0] = 0;

	//deklarasi pembuatan list
	(*max).first = NULL;
		
	for(i=1; i<=(*L).first->max_level; i++){
		//deklarasi awal banyak spasi
		spasi[i] = 0;
	
		//variabel pointer untuk loop
		elemen *bantu = S.top;

		//proses loop
		while(bantu != NULL){

			if(bantu->level == i){
				if((strlen(bantu->elmt.kebaikan) > spasi[i])){			
					spasi[i] = strlen(bantu->elmt.kebaikan);
				}
			}
			//increment
			bantu = bantu->next;
		}
	}

	//deklarasi list untuk max
	createList(max);


	//proses penjumlahan spasi
	//-1 karena untuk kata terpanjang pada level terdalam tidak terpakai, hemat loop
	for(i=0; i<(*L).first->max_level-1; i++){
		spasi[i+1] = spasi[i] + spasi[i+1] + 1;
	}
	//pengcopyan ke list
	for(i=0; i<(*L).first->max_level; i++){
		addLast(spasi[i],max);
	}
	


}

//prosedur pembuatan list
void createList(list *L){
	(*L).first = NULL;
}

//prosedur pembuatan list
void createList_isi(list_isi *L){
	(*L).first = NULL;
}


//prosedur input data ke list menggunakan metode first
void addFirst(int max_level ,list *L){

	elemenList *baru;
	baru = (elemenList *) malloc (sizeof (elemenList));
	
	baru->max_level = max_level ;

	if((*L).first == NULL){
		baru->next = NULL;
	}else{
		baru->next = (*L).first;
	}

	(*L).first = baru;
	baru = NULL;
}

//add secara after untuk list
void addAfter(elemenList *prev, int max_level, list *L){
	//kondisi saat prev tidak kosong
	if(prev != NULL){

		elemenList *baru;
		baru = (elemenList*) malloc (sizeof (elemenList));
		//copy isi
		baru->max_level = max_level;

		if(prev->next == NULL){
			baru->next = NULL;
		}else{
			baru->next = prev->next;
		}

		prev->next = baru;
		baru = NULL;

	}

}

//add secara terakhir untuk list
void addLast(int max_level,list *L){

	if((*L).first == NULL){
		//jika list kosong
		addFirst(max_level,L);
	}else{
		//jika list tidak kosong
		//mencari elemen terakhir list
		elemenList *prev = (*L).first;
		while(prev->next != NULL){
			//iterasi
			prev = prev->next;
		}
		addAfter(prev,max_level,L);
	}
}


//prosedur input data ke list menggunakan metode first
void addFirst_isi(char *info ,list_isi *L){

	elemenList2 *baru;
	baru = (elemenList2 *) malloc (sizeof (elemenList2));
	strcpy(baru->kebaikan,info);

	if((*L).first == NULL){
		baru->next = NULL;
	}else{
		baru->next = (*L).first;
	}

	(*L).first = baru;
	baru = NULL;
}

//add secara after untuk list
void addAfter_isi(elemenList2 *prev, char *info, list_isi *L){
	//kondisi saat prev tidak kosong
	if(prev != NULL){

		elemenList2 *baru;
		baru = (elemenList2 *) malloc (sizeof (elemenList2));
		//copy isi
		strcpy(baru->kebaikan,info);

		if(prev->next == NULL){
			baru->next = NULL;
		}else{
			baru->next = prev->next;
		}

		prev->next = baru;
		baru = NULL;

	}

}

//add secara terakhir untuk list
void addLast_isi(char *info, list_isi *L){

	if((*L).first == NULL){
		//jika list kosong
		addFirst_isi(info,L);
	}else{
		//jika list tidak kosong
		//mencari elemen terakhir list
		elemenList2 *prev = (*L).first;
		while(prev->next != NULL){
			//iterasi
			prev = prev->next;
		}
		addAfter_isi(prev,info,L);
	}
}
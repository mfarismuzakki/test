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
//								kwkwkwkwwk			     	 CODED BY : Muhammad Faris Muzakki 1606923 			   													//
//														    		ILMU KOMPUTER 2016																		//
//																																							//
//                                              Saya Muhammad Faris Muzakki Mengerjakan evaluasi TMD		        										//
//                                     	      dalam matakuliah struktur data untuk keberkahannya maka saya tidak 											//
//										   	   melakukan kecurangan seperti yang telah dispesifikan. Aamiin				 									//
//	                                        																							     				//
//											                                													    						//
//		   											       																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// #include "header.h"
#include "mesin.c"
int main(){
	
	/*
	penjelasan alur kerja program
		1. pisah jenis dari input (nama ayah, nama anak, jumlah kebaikan)
		2. input inputan ke dalam pohon
		3. untuk kebaikan, ditampung di tree dengan menggunakan bantuan list
		4. mencari level dari dari masing masing simpul (setelah addchild)
		5. mencari level terdalam (berbarengan dengan proses input) => hasilnya di tampung didalam list
		6. menampung seluruh kebaikan dan nama anak di dalam stack untuk menentukan masing masing jumlah spasi => ditampung didalam list
		7. hapus stack penampung isi pohon(agar hemat memory)
		8. print isi pohon secara preeOrder dengan jumlah spasi diawal yang telah ditentukan pada tahap 5
		9. mancari nama nama yang dicari menggunakan algoritma print, lalu di print
		10. mancari kebaikan nama nama yang dicari menggunakan algoritma print, lalu di print
		11. mencari daun menggunakan rekursif dengan cara mencari level tertinggi dari jalur yg sudah ditentukan oleh soal
	*/

	//deklarasi tree
	tree T;
	//stack untuk tampung isi tree					
	stack S; 					
	//List untuk menentukan max level 						
	list L;
	//list untuk tampung max spasi
	list max;


	//penanda daun terakhir 	
	simpul *daun; 				

	//deklarasi variabel penampung input
	char input[500];
	int banyak;

	//deklarasi variabel pemisah 
	char orangtua[500];
	char nama_anak[500];
	int jumlah_kondisi;

	//deklarasi variabel iterator
	int i,j;

	//deklarasi awal kedalaman maximum di tampung dalam list
	createList(&L);
	//isi kedalaman default yaitu 0
	addFirst(0,&L);
	
	//peninputan dari user
	scanf("%d",&banyak);
	for(i=0; i<banyak; i++){
		//input
		scanf("%s",&input);
		
		//pisah jenis dari inputan
		pisah(input,orangtua,nama_anak,&jumlah_kondisi);

		//input pertama penjadi parent of tree
		if(i==0){
			makeTree(nama_anak,&T);
			//mengisi tingkat pohon
			isi_level(nama_anak,T);
			cari_max(nama_anak,T,&L);
		}else{
			//tampung kebaikan anak
			container tampung_kebaikan[jumlah_kondisi];
			//input isi kebaikan anak
			for(j=0; j<jumlah_kondisi; j++){
				scanf("%s",&tampung_kebaikan[j].kebaikan);
			}
			//input anak2
			//pointer penanda posisi bapak
			simpul *bantu = findSimpul(orangtua,T.root);	
			addChild(nama_anak,bantu,tampung_kebaikan,jumlah_kondisi);
			// isi_level
			isi_level(nama_anak,T);
			cari_max(nama_anak,T,&L);
		}	
	}

	//input data yang ingin di searching
	int banyak2;
	scanf("%d",&banyak2);
	//variabel penampung nama nama yang akan dicari
	char cari[banyak2][500];
	for(i=0; i<banyak2; i++){
		scanf("%s",&cari[i]);
	}


	//memindahkan isi tree ke stack untuk menghitung spasi masing masing level
	createEmpty(&S); //deklarasi awal Stack
	pindah_stack(T.root,&S);

	//menghitung masing masing spasi tiap level
	hitung_spasi(S,&L,&max);

	//menghapus seluruh isi stack, karena sudah tidak diperlukan
	popAll(&S);
	//hapus keberadaan Stack
	free(S.top);

	// //print isi pohon secara pre order
	elemenList *max_spasi = max.first;
	printTreePreOrder(T.root,max_spasi);
	

	printf("\n");
	//print input pertama dengan cara mencari data input di tree 
	cari_nama(banyak2,cari,T);
	printf("\n");
	//print isi dari kebaikan yang dicari
	cari_kebaikan(banyak2,cari,T);
	printf("\n");
	//cari daun terakhir + print
	cari_daun(findSimpul(cari[banyak2-1],T.root),&L,&daun);
	printf("\n");

	//print isi daun terakhir
	print_nama(daun->info,2,daun); 

	//hapus list untuk menghitung max kedalam
	free(L.first);
	//menghapus pointer agar hemat memori
	free(daun);
  return 0;
}

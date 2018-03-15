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
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
jangan di errorrrin :9 wkwkwkwk


//penampung inputan
typedef struct {
	char kebaikan[500];
}container;

//-----------------List1-------------------//
//deklarasi pembungkus variabel bungkusan  //
typedef struct elm *alamatelmtList;	  	   //
typedef struct elm{ 					   //
	//maximal spasi 					   //
	int max_level; 						   //
	alamatelmtList next; 				   //
	 									   //
}elemenList; 							   //
 										   //
//deklarasi list 						   //
typedef struct  						   //
{ 										   //
	elemenList *first; 					   //
}list; 									   //
//-----------------------------------------//

//-----------------List2-------------------//
//deklarasi pembungkus variabel bungkusan  //
typedef struct elm2 *alamatelmtList2;	   //
typedef struct elm2{ 					   //
	//maximal spasi 					   //
	char kebaikan[500]; 				   //
	alamatelmtList2 next; 				   //
	 									   //
}elemenList2; 							   //
 										   //
//deklarasi list 						   //
typedef struct  						   //
{ 										   //
	elemenList2 *first; 			 	   //
}list_isi; 							       //
//-----------------------------------------//

//---------------Tree----------------//
//dekalrasi variabel penampung data  //
typedef struct smp *alamatsimpul;	 //
typedef struct smp{                  //
  char info[500];					 //
  list_isi isi;                      // 
  int level; 	     		         //
  alamatsimpul sibling;				 //
  alamatsimpul child;                //
}simpul;                             //
									 //
typedef struct{                      //
  simpul* root;                      //
}tree;                               //
//-----------------------------------//

//---------------Stack---------------//
//dekalrasi variabel penampung data  //
typedef struct elmt *alamatelmt;	 //
typedef struct elmt{				 //
	container elmt;					 //
	int level;						 //
	alamatelmt next;				 //
}elemen;							 //
									 //
//dekalrasi stack 					 //
typedef struct{						 //
	elemen* top;					 //
}stack;								 //
//-----------------------------------//



//-------------------------------Prosedur Olah Input---------------------------------//
//prosedur untuk memisahkan jenis inputan dari inputan utama						 //
void pisah(char *inputan,char *orangtua,char *nama_anak,int *jumlah_kondisi); 	     //
//print nama nama yang dicari 														 //
void cari_nama(int banyak ,char nama[banyak][500], tree T); 					     //
//prosedur print nama yang dicari 													 //
void print_nama(char nama[],int status, simpul *root); 								 //
//print nama nama yang dicari 														 //
void cari_kebaikan(int banyak ,char nama[banyak][500], tree T); 					 //
//mencari daun 																		 //
void cari_daun(simpul *root, list *L, simpul **daun); 								 //
//hitung kedalaman simpul 															 //
int cari_Level(simpul *root, char *nama, int level); 								 //
//mengisi level tree 																 //
void isi_level(char *nama, tree T); 												 //
//menentukan kedalaman maximum														 //
void cari_max(char *nama, tree T, list *L); 										 //
//memindahkan isi tree ke stack  													 //
void pindah_stack(simpul *root, stack *S); 							                 //
//prosedur cari daun 																 //
void cari_tanda_daun(simpul *root, list *L, simpul **daun);							 //
//hitung spasi 																		 //
void hitung_spasi(stack S, list *L,list *max); 										 //		
//copy daun																			 //
void copy_daun(simpul *root, list *L, simpul **daun);								 // 
//-----------------------------------------------------------------------------------//


//------------------------Prosedur Default Pohon----------------------//
//membuat Pohon 										     		  //
void makeTree(char *info, tree *T);									  //
//menambahkan anak 													  //
void addChild(char *info, simpul *root, container *isi, int banyak);  //
//mencari simpul													  //
simpul* findSimpul(char *info, simpul *root); 						  //			
//---------------print isi pohon-----------------------------// 	  //									
void printTreePreOrder(simpul *root,elemenList *max);		 //		  //	
//-----------------------------------------------------------//       //
//--------------------------------------------------------------------//
	  

//------------------------Prosedur Default Stack----------------------//
//prosedur membuat stack 											  //
void createEmpty(stack *S); 										  //
//prosedur pengecekan apakah stack kosong 							  //
int isEmpty(stack S); 												  //
//prosedur penghitung jumlah isi stack 								  //
int countElement(stack S); 											  //
//add data 															  //
void push(char nama[],int level, stack *S); 						  //
//delete data 														  //
void popAll(stack *S); 												  //
//print stack 														  //
void printStack(stack S); 											  //
//--------------------------------------------------------------------//


//-----------------------Prosedur Default List------------------------//
//prosedur pembuatan List 											  //
void createList(list *L); 											  //
//prosedur pembuatan List 											  //
void createList_isi(list_isi *L);									  //
//prosedur input data ke list menggunakan metode first 				  //
void addFirst(int max_level, list *L); 								  //
//add secara terakhir untuk list 									  //
void addLast(int max_level, list *L); 								  //
//add secara after untuk list 										  //
void addAfter(elemenList *prev, int max_level, list *L); 		      //
//prosedur input data ke list menggunakan metode first 				  //
void addFirst_isi(char *info, list_isi *L); 						  //
//add secara terakhir untuk list 									  //
void addLast_isi(char *info, list_isi *L);	 						  //
//add secara after untuk list 										  //
void addAfter_isi(elemenList2 *prev, char *info, list_isi *L); 		  //
//--------------------------------------------------------------------//

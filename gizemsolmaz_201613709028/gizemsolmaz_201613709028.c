#include<stdio.h>
#include<stdlib.h>
/*
*   GİZEM SOLMAZ
*   201613709028
*/


typedef struct node
{
    int data;   //verilerin tutulacağı yer
    struct node* next;  //eklenecek veriden sonraki verinin adresini tutar.
}mySlot;

void olusturma(mySlot* slot, int size) //oluşacak liste fonksiyonu
{
    for (int i = 0; i < size; i++)  //giirlen size değeri kadar dönen for
    {
        //ilk ve sonraki bütün değerler öncelikle null olarak atandı
        (slot + i)->data = NULL;
        (slot + i)->next = NULL;
    }
}

void ekleme(int value, mySlot* slot, int size)   //ekleme yapmak için fonksiyon oluşturuldu 
{
    //
    struct node* newNode = malloc(sizeof(struct node));     //newNode adında boş bir alan açtık
    newNode->data = value; //newNode alanına value yani kullanıcıın girdiği eklenecek sayıyı giriyoruz
    newNode->next = NULL;  // newNode'un sonra ki düğümünü NULL olarak yazdırıyoruz.
    int key = value % size;     //eklememiz gereken asıl slot indexini key değerine atıyoruz
    //slot[key] olarak düşündüğüm şey key bizim modumuz yani eklenecek verinin uygun oldupu index değerini veriyor.
    if (slot == NULL)  //eklenecek verinin slot[key] u boş ise eğer; //ama slot[key] yazdığım takdirde aşamadığım bir sorunla karşılaştım
        slot = newNode;    //slot[key} değeri yeni girilen değer olmuş oldu //ama slot[key] yazdığım takdirde aşamadığım bir sorunla karşılaştım
    else    //eklenecek sayının slot[key] u boş değilse eğer;
    {
        struct node* temp = slot;   //temp i slot[key] yapmak istedim ama hata veriyor.
        while (temp->next)  //temp i next e ekliyorum
        {
            temp = temp->next;  //temp in nextini temp e atıyorum yani yeni temp verinin eklenmiş hali oluyor
        }
        temp->next = newNode;   //ve eklemeden sonra ki temp tekrar NULL oluyor
    }
}
int silme_islemi(int value, mySlot* slot, int size) //silme işlemleri için "silme_islemi" adında fonksiyon oluşturduk. İçindeki value değeri "int main" kısmında kullanıcının silmek istediği değer yerine geçiyor
{
    int key = value % size; //silinmek istenen veri ile yığın sayısının bölümünden kalan (modu) key değerine atanır
    struct node* temp = slot, * dealloc;   //
    if (temp != NULL)   //temp değerimizin NULL olmadığında bakılır
    {
        if (temp->data == value)    //temp imizin datası value yani girilen değer olduğunda 
        {
            dealloc = temp;     //temp serbest bırakılır ve
            temp = temp->next;  //temp in next i yani null temp yerine geçiyor
            free(dealloc);  //serbest bırakılır
            return 1;   //döndürme işlemi yapılır
        }
        else    //temp imizin datası value yani girilen değer olmadığı zaman 
        {
            while (temp->next)   ////temp'in next'i olduğu sürece dönecek
            {
                if (temp->next->data == value)
                {
                    dealloc = temp->next;   //temp in istenilen değeri serbest bırakılır yani silinmiş olur
                    temp->next = temp->next->next;  // ve temp in 2*next i bu da NULL değeri oluyor yeni temp->next yani silinen değer yerine geçmiş oluyor.
                    free(dealloc);  //işlem burada biter
                    return 1;
                }
                temp = temp->next;
            }
        }
    }
    return 0;
}
void listeyi_yazdir(mySlot* slot, int size)
{
    int i;
    for (i = 0; i < size; i++) //girilen slot sayısı kadar dönecek for açıldı
    {
        struct node* temp = slot;   //slotumuzu temp'e atıyoruz 
        printf("\tslot[%d]-->", i);     //slot sayısı kadar yazdırır
        while (temp)    //
        {
            if (!temp->data == NULL)     //temp->data'mız NULL olmadğında 
                printf("%d -->", temp->data);   //son düğüm yazılmazdı
            temp = temp->next;  //temp'in nextini yeni tempe atadık
        }
        printf("NULL\n");   //null olduğunu göstermek için printf ile yazdırdık
    }
    printf("\n");
}
int main()
{
    int slot_sayisi;    //yığın sayısı belirleniyor.
    printf("Slot sayisini girin: ");     //kullanıcı slot istediği slot sayısını girer
    scanf_s("%d", &slot_sayisi);    //girilen slot sayısı tutulur
    mySlot* slot = malloc(slot_sayisi * sizeof * slot);

    olusturma(slot, slot_sayisi); //yığınımizi önce NULL olarak getirdik.

    printf(" ---- Listenin bos hali ---- \n");
    listeyi_yazdir(slot, slot_sayisi);   //listemizin boş halini yazdırır

    int eklenecek, silinecek, i = 0, islem;
basa:
    printf("Veri ekleme --> 1\tVeri silme --> 2\tCikis yapmak icin --> 3\nYapmak istediginiz islemi secin: ");    //kullanıcıya seçimi sorulur
    scanf_s("%d", &islem);  //silme işlemleri için girilen veri tutuluyor

    if (islem == 1)     // kullanıcının seçtiği işlem eğer 1 yani ekleme işlemi ise;
    {
        printf("Eklemek istediğiniz sayiyi girin: ");   //kullanıcı eklemek istediği veriyi girer
        scanf_s("%d", &eklenecek);  //veri tutulur
        ekleme(eklenecek, slot, slot_sayisi);  //ekleme fonksiyonuna eklenecek veri gönderilir
        listeyi_yazdir(slot, slot_sayisi);   //verinin eklendiği yeni liste ekrana yazdırılır
        goto basa;  //kullanıcıya tekrar ne yapmak istediğini sormak için goto kulladnım
    }
    else if (islem == 2)    // kullanıcının seçtiği işlem eğer 2 yani silme işlemi ise;
    {
        printf("Cıkarmak istediğiniz sayiyi girin: ");   //kullanıcı silmek istediği veriyi girer
        scanf_s("%d", &silinecek);   //veri tutulur
        if (silme_islemi(silinecek, slot, slot_sayisi))     //silinmek istenen veri silme_islemi fonksiyonuna gönderilir.
        {
            printf("Veri silindikten sonra:\n");
            listeyi_yazdir(slot, slot_sayisi);   //girilen veri silindikten sonra ki 
            goto basa;   //tekrar seçim satırına geçer
        }
        else
        {
            printf("Boyle bir veri mevcut degil.\n");   //silinmek istenen veri silme_islemi fonksiyonu içinde 
            goto basa;   //tekrar seçim satırına geçer
        }
    }
    else if (islem == 3)    //programı sonlandırmak için seçilir
    {
        exit(0); //sonlandırılır
    }
    else
    {
        printf("HATALI GIRIS YAPTINIZ");    //kullanıcıya verilen 1-2-3 seçenekleri harici bir giriş yaptığı takdirde uyarı verir ve,
        goto basa;   //tekrar seçim satırına geçer
    }
    return 0;
}
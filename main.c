#include <stdio.h>
#include <stdlib.h>

typedef struct node *Node;

typedef struct node {
    int data;
    Node right, down;
}node;

Node createNode(int data)
{
    Node temp = (Node)malloc(sizeof(Node));
    temp->data = data;
    temp->right = NULL;
    temp->down = NULL;
    return temp;
}

void freeList(Node head){

    Node tmp;
    Node downPointerForHead = head;

    while (downPointerForHead != NULL) {
        Node rightPointerForHead = downPointerForHead;
        rightPointerForHead = rightPointerForHead->right;
        while (rightPointerForHead != NULL) {
            tmp = rightPointerForHead;
            rightPointerForHead = rightPointerForHead->right;
            free(tmp);
        }
        downPointerForHead = downPointerForHead->down;
    }

}


node* construct( int m, int n)
{
    Node head = NULL;
    Node heads[m];
    Node rightTemp, newptr;
    
    for (int i = 0; i < m; i++) {
        heads[i] = NULL;
        for (int j = 0; j < n; j++) {
            newptr = createNode(NULL);

            if (head == NULL) {
                head = newptr;
            }
            if (heads[i] != NULL) {
                rightTemp->right = newptr;
            } else {
                heads[i] = newptr;
            }
            rightTemp = newptr;
        }
    }

    for (int i = 0; i < m - 1; i++) {
        Node temp1 = heads[i];
        Node temp2 = heads[i + 1];
        while ((temp1 != NULL) && (temp2 != NULL)) {
            temp1->down = temp2;
            temp1 = temp1->right;
            temp2 = temp2->right;
        }
    }

    return head;
}

Node copy(Node head1,Node head2){
    Node rightPointerForHead1;
    Node downPointerForHead1 = head1;

    Node rightPointerForHead2;
    Node downPointerForHead2 = head2;

    while (downPointerForHead2) {
        rightPointerForHead2 = downPointerForHead2;
        rightPointerForHead1 = downPointerForHead1;

        while (rightPointerForHead2 ) {
            //Dataların atılması
            rightPointerForHead1->data = rightPointerForHead2->data;
            rightPointerForHead2 = rightPointerForHead2->right;
            rightPointerForHead1 = rightPointerForHead1->right;
        }

        downPointerForHead2 = downPointerForHead2->down;
        downPointerForHead1 = downPointerForHead1->down;
    }
    return head1;
}

Node add(Node head, int data, int x, int y){
    Node temp;
    Node newHead = head; // Eğer yeni bir matris oluşturulursa
    int n = 0;
    int m = 0;
    int maxM;
    int maxN;

    //Beklentideki matrisin kenar uzunlarının bulunması-----
    temp=head;
    while(temp){
        n++;
        temp = temp->right;
    }
    temp=head;
    while(temp){
        m++;
        temp = temp->down;
    }

    if(m>x){
        maxM = m;
    }else{
        maxM = x;
    }
    if(n>y){
        maxN = n;
    }else{
        maxN = y;
    }
    // Birleştirme yapma durumları
    // [2][5]'iken (3,5) gelirse matrisi büyütmeliyiz
    if(m<x || n<y){
        temp = construct(maxN+1, maxM+1);
        // Kullanılan matris uzunlukları değişti o halde globalleri güncelleyelim.
        m = maxM;
        n = maxN;
        newHead = copy(temp,head);
        freeList(head);
        // yeni matrisi oluştur
        // eskini aynen kopyala
        //temp = construct(data,0,0,maxM,maxN);
    }

    // Yeni matris oluşturulmadıysa newHead = head yani temp = head
    temp = newHead;
    //sağa gidiş
    for(int i=0;i<x;i++){
        temp = temp->right;

    }
    //aşağı gidiş
    for(int j=0;j<y;j++){
        temp = temp->down;
    }
    // İstenilen yere geldik ve onun datasını gönderilen dataya çevirdik
    temp->data = data;
    return newHead;
}


// utility function for displaying
// linked list data
void display(Node head)
{
    // pointer to move right
    Node Rp;
    // pointer to move down
    Node Dp = head;

    // loop till node->down is not NULL
    while (Dp) {
        Rp = Dp;
        // loop till node->right is not NULL
        while (Rp) {
            if(Rp->data==NULL){
                printf("\t*");
            }else{
                printf("\t%d",Rp->data);
            }
            printf(" ");
            Rp = Rp->right;
        }
        printf("\n");
        Dp = Dp->down;
    }
}

int main() {
    Node head=createNode(NULL);
    int arr[] = { 5, 4, 8, 3, 27, 10,39};
    int arr1[] = { 2, 0, 1, 1, 3, 5,7};
    int arr2[] = { 2, 2, 0, 4, 3, 5,5};

    for(int i = 0; i<7;i++){
        head = add(head,arr[i],arr2[i],arr1[i]);
        printf("\n Adım %d: \n",i+1);
        display(head);
    }
    return 0;
}

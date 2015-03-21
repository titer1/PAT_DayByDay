#define REF_2_1 //revert_list
#ifdef REF_2_1 //basic


#include <stdio.h>

#define MAX_SIZE 100004

typedef struct tagLNode{
    int addr;      //�ڵ�λ��Address
    int data;      //Dataֵ
    int nextAddr;  //�¸��ڵ�λ��
    struct tagLNode *next;  //ָ���¸��ڵ��ָ��
} LNode;
/*
    LNode *listReverse(LNode *head, int k);  
    ��ת��������
    ����1���������ͷ�ڵ㣬
    ����2����ת������ĳ��ȣ�
    ����ֵ����ת�������ĵ�һ���ڵ�(����ͷ���)

*/
LNode *listReverse(LNode *head, int k);  
//��������� ����Ϊ�������ͷ���
void printList(LNode *a);


#define MAX_N 100000
 LNode a[MAX_N +1];                //�ܴ�n+1����������顣

//int main()
 int p1074_main()
{
    int firstAddr;
    int n = 0;            //�ڵ��� N
    int k = 0;            //��ת������ĳ���K
    int num = 0;          //������֮�������ڵ���
    int data[MAX_SIZE];   //��dataֵ �ڵ�λ����Ϊ����ֵ
    int next[MAX_SIZE];   //��nextֵ �ڵ�λ��Ϊ����
    int tmp;              //��ʱ�����������ʱ����
   
//#define _F
#ifdef _F
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
    scanf("%d %d %d", &firstAddr, &n, &k);    
   // LNode a[n+1];                //�ܴ�n+1����������顣
    a[0].nextAddr = firstAddr;   //a[0] ��Ϊͷ�ڵ�
    //������Ľڵ�
    int i = 1;    
    for (; i < n+1; i++){
        scanf("%d", &tmp);
        scanf("%d %d", &data[tmp], &next[tmp]);        
    }

 //��������   
    //����������
    i = 1;
	//while init a[0]..though it is not used;
	//and give the while the entrance,
    while (1){
        if (a[i-1].nextAddr == -1){
            a[i-1].next = NULL;
            num = i-1;
            break;            
        }
        a[i].addr = a[i-1].nextAddr;//first 
        a[i].data = data[a[i].addr]; 
        a[i].nextAddr = next[a[i].addr];
        a[i-1].next = a+i;
                
        i++;
    }
 
//�����ѵ��ڴˣ����ġ�
//��Ҫ�� num ,k
//Ȼ����Կձ�ͷ a[0]...���з��ص���ÿ�������е�β�ͣ�2�������е����ӣ�ͷ������,�����β�����£���
    LNode *p = a;                    //pָ������ͷ���
    LNode *rp = NULL;                //��ת�������ķ���ֵ
    //�ֲ���ת
	if (k <= num ){
        
        for (i = 0; i < (num/k); i++){
            rp = listReverse(p, k);  //
            p->next = rp;            // ��һ��ִ�У�a[0]->next ָ���һ��������ת�ĵ�һ���ڵ�
            p->nextAddr = rp->addr;  // ����Nextֵ��ָ����ת��������һ���ڵ��λ��
            
            int j = 0;
            //ʹpָ����һ����Ҫ��ת���������ͷ��㣨��һ���ڵ��ǰһ���ڵ㣩
            //while (j < k){
            //    p = p->next;
            //    j++;
            //}
			p = rp; //ֱ�ӷŵ�ĩβ
        
        }
    }

    printList(a);   
	return 0;
}

LNode *listReverse(LNode *head, int k)
{
    int count = 1;
    LNode *newOne = head->next;
    LNode *old = newOne->next;
    LNode *tmp = NULL;
    
    while (count < k){
        tmp = old->next;
        old->next = newOne;
        old->nextAddr = newOne->addr;
        newOne = old;   //new�����һ���ڵ�
        old = tmp;   //tmp�����һ���ڵ�
        count++;
    }
    //ʹ��ת������һ���ڵ�ָ����һ��������ĵ�һ���ڵ�
    head->next->next = old;  
    if (old != NULL){
        //�޸�Nextֵ��ʹ��ָ����һ���ڵ��λ��
        head->next->nextAddr = old->addr; 
    }else{
        //���oldΪNULL,��û����һ����������ô��ת������һ���ڵ㼴�������������һ���ڵ�
        head->next->nextAddr = -1;       
    }
    return newOne;
}

void printList(LNode *a)
{
    LNode *p = a;
    
    while (p->next != NULL){
        p = p->next;        
        if (p->nextAddr != -1 ){
            //��ʽ�����%.5��ζ�����һ����������5λ�����ʱǰ�油0 �磺22�������00022
            printf("%.5d %d %.5d\n", p->addr, p->data, p->nextAddr);
        }else{
            //-1����Ҫ��%.5��ʽ���
            printf("%.5d %d %d\n", p->addr, p->data, p->nextAddr);
        }    
    }

}


/*
00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218

���Ե�һ����7���� 
L ��������ڵ�����
��Ϊ���ɵ�����Ľڵ㲻һ�����������N���ڵ��У�����L<=N;

case 0��L = N    �нڵ� Address = 99999

case 1: L = m*K,  L = N, (m = 2, 3, 4,...)  �нڵ� Address = 99999

case 2: K = N,  L = N      �нڵ� Address = 99999

case 3: K = 1,  L = m*K   �нڵ� Address = 99999

case 4: K = 1,  L = N = 1       ���ܼ򵥵�һ�����Ե㣩

case 5: K != 1, L % K = (K-1)   ���ڵ����ܶ࣬���������ĸ��Ӷ���O(n*n), ��ʱ�Ŀ����Ժܴ�

case 6: L > N ���ж���ڵ㣩  �нڵ�Address = 99999

Ҫ���ǵ�ϸ�ڣ�K=1����ת��K=L ȫ��ת��L%K == 0, ÿ�ζ���ת��L%k = (K-1),����Ľڵ㲻��ת��L<N���ж���ڵ�������


*/
#endif

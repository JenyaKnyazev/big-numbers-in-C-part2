#include <stdio.h>
#include <stdlib.h>
/*
    made by Jenya Knyazev
*/
/*
    arithmetic operations on big numbers in C
    the big numbers represents by lists of characters
*/
typedef struct{
    char data;
    struct list *next;
    struct list *prev;
}list;

list *head=NULL;
list *tail=NULL;
list *head2=NULL;
list *tail2=NULL;
list *head_result=NULL;
list *tail_result=NULL;
list *head_div=NULL;
list *tail_div=NULL;

list* generate_node_list(char ch){
    list *p=(list*)malloc(sizeof(list));
    p->data=ch-48;
    p->prev=NULL;
    p->next=NULL;
    return p;
}
void add_to_start(list *p,list **HEAD,list **TAIL){
    if(*HEAD==NULL){
        *HEAD=p;
        *TAIL=p;
    }else{
        p->next=*HEAD;
        (*HEAD)->prev=p;
        *HEAD=p;
    }
}
void print_list(list *p){
    if(p==NULL)
        puts("The list is empty\n");
    while(p!=NULL){
        putchar(p->data+48);
        p=p->next;
    }
}
void print_list_reverse(list *p){
    if(p==NULL)
        puts("The list is empty\n");
    while(p!=NULL){
        putchar(p->data+48);
        p=p->prev;
    }
}
void add_to_end(list *p,list **_head,list **_tail){
    if(*_head==NULL){
        *_head=p;
        *_tail=p;
    }else{
        p->prev=*_tail;
        (*_tail)->next=p;
        *_tail=p;
    }
}
void scan_list(list **head_,list **tail_){
    char ch=getchar();
    while(ch!='\n'){
        add_to_end(generate_node_list(ch),head_,tail_);
        ch=getchar();
    }
}
void clean_list(list **head_,list **tail_){
    list *p,*p2;
    p=*head_;
    while(p!=NULL){
        p2=p->next;
        free(p);
        p=p2;
    }
    *head_=*tail_=NULL;
}
void remove_one_element_from_start(list **head_,list **tail_){
    list *p=*head_;
    if(*head_!=NULL){
        if(*head_==*tail_){
            free(*head_);
            *head_=*tail_=NULL;
            return;
        }
        *head_=(*head_)->next;
        (*head_)->prev=NULL;
        free(p);
    }
}
void refresh(list **h,list **t){
    list *p=*t;
    int n=0;
    if(*t==NULL)
        return;
    do{
        p->data+=n;
        n=p->data/10;
        p->data=p->data%10;
        p=p->prev;
    }while(p!=NULL);
    if(n)
        add_to_start(generate_node_list(n+48),h,t);
}
void refresh2(list **h,list **t){
    list *p=*h,*p2;
    if(*h==NULL)
        return;
    while(p->next!=NULL){
        (p->data)--;
        p=p->next;
        p->data+=10;
    }
    refresh(h,t);
    p=*h;
    while(p->next!=NULL&&p->data==0){
        p=p->next;
        remove_one_element_from_start(h,t);
    }
}
void plus(list *tail11,list *tail22){
    list *p=tail_result;
    while(tail11!=NULL){
        if(p==NULL){
            add_to_start(generate_node_list('0'),&head_result,&tail_result);
            p=head_result;
        }
        p->data+=tail11->data;
        p=p->prev;
        tail11=tail11->prev;
    }
    p=tail_result;
    while(tail22!=NULL){
        if(p==NULL){
            add_to_start(generate_node_list('0'),&head_result,&tail_result);
            p=head_result;
        }
        p->data+=tail22->data;
        p=p->prev;
        tail22=tail22->prev;
    }
    refresh(&head_result,&tail_result);
}
void minus(list *tail_1,list *tail_2){
    plus(tail_1,NULL);
    list *p=tail_result;
    while(tail_2!=NULL){
        (p->data)-=tail_2->data;
        p=p->prev;
        tail_2=tail_2->prev;
    }
    refresh2(&head_result,&tail_result);
}
void decrease_by_one(list **h,list **t){
    ((*(*t)).data)--;
    refresh2(h,t);
}

int is_empty(list *tail_){
    if(tail_==NULL||tail_->prev==NULL&&tail_->data==0)
        return 1;
    return 0;
}
void multiply(list *tail_1,list **h,list **t){
    while(is_empty(*t)==0){
        plus(tail_1,NULL);
        decrease_by_one(h,t);
    }
}
void increase_by_one(list **h,list **t){
    if(*h==NULL)
        add_to_start(generate_node_list('0'),h,t);
    (*t)->data++;
    refresh(h,t);
}

int is_bigger(list *p,list *p2){
    list *t1=p,*t2=p2;
    while(t1!=NULL&&t2!=NULL){
        t1=t1->next;
        t2=t2->next;
    }
    if(t1!=NULL&&t2==NULL)
        return 1;
    if(t2!=NULL&&t1==NULL)
        return -1;
    while(p!=NULL){
        if(p->data>p2->data)
            return 1;
        if(p->data<p2->data)
            return -1;
        p=p->next;
        p2=p2->next;
    }
    return 0;
}
void division(list *h,list *h2){
    while(is_bigger(h,head_result)!=-1){
        plus(h2,NULL);
        increase_by_one(&head_div,&tail_div);
    }
    decrease_by_one(&head_div,&tail_div);
}
void clean_buff(){
    while(getchar()!='\n');
}
void run(){
    char ch;
    printf("Arithmetic operations on big numbers in C\n");
    while(1){
        printf("\nEnter arithmetic operator + - * / exit enter @\n");
        scanf("%c",&ch);
        if(ch=='@')
            break;
        clean_buff();
        printf("Enter first number\n");
        scan_list(&head,&tail);
        printf("Enter second number\n");
        scan_list(&head2,&tail2);
        printf("Result = ");
        switch(ch){
            case '+':
                plus(tail,tail2);
                print_list(head_result);
                break;
            case '-':
                minus(tail,tail2);
                print_list(head_result);
                break;
            case '*':
                multiply(tail,&head2,&tail2);
                print_list(head_result);
                break;
            case '/':
                division(head,tail2);
                print_list(head_div);
                break;
        }
        clean_list(&head,&tail);
        clean_list(&head2,&tail2);
        clean_list(&head_result,&tail_result);
        clean_list(&head_div,&tail_div);
    }
}
int main(){
    run();
    puts("\nExit enter\n");
    //while(getchar()!='\n');
    getchar();
    return 0;
}



























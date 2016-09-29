/******************************************************************************
 * @file    : list_test.c
 * @author  : wangyubin
 * @date    : Sun Jun 22 19:00:58 2014
 * 
 * @brief   : list test use CppUTest
 * history  : init
 ******************************************************************************/

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

extern "C"
{
#include "list.h"
}

struct test_struct 
{
    int num;
    struct list_head list;
};

void print_list(struct list_head *h);
void init_test_struct(int n, struct test_struct* ts);
    
TEST_GROUP(test_list)
{
    void setup()
    {
        printf ("\n=========================================\n");
    }
    void teardown()
    {
        printf ("=========================================\n\n\n");
    }
};

/* 追加2个节点，然后和head.next head.prev 比较地址 */
TEST(test_list, list_add)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(2 * sizeof(struct test_struct));
    init_test_struct(2, ts);
    
    LIST_HEAD(head);
    printf ("Before add node:\n");
    print_list(&head);
        
    printf ("After add node:\n");
    list_add(&(ts+0)->list, &head);
    list_add(&(ts+1)->list, &head);
    print_list(&head);

    POINTERS_EQUAL(&(ts+1)->list, head.next);
    POINTERS_EQUAL(&ts->list, head.prev);

    free(ts);
}

/* 追加2个节点，然后和head.next head.prev 比较地址 */
TEST(test_list, list_add_tail)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(2 * sizeof(struct test_struct));
    init_test_struct(2, ts);
    
    LIST_HEAD(head);
    printf ("Before add node:\n");
    print_list(&head);
        
    printf ("After add node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    POINTERS_EQUAL(&ts->list, head.next);
    POINTERS_EQUAL(&(ts+1)->list, head.prev);

    free(ts);
}

TEST(test_list, list_del)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(2 * sizeof(struct test_struct));
    init_test_struct(2, ts);
    
    LIST_HEAD(head);
    printf ("Before del node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    printf ("After del node:\n");
    list_del(&(ts+0)->list);
    print_list(&head);
    
    free(ts);
}

TEST(test_list, list_del_init)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(2 * sizeof(struct test_struct));
    init_test_struct(2, ts);
    
    LIST_HEAD(head);
    printf ("Before del node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    printf ("After del node:\n");
    list_del(&(ts+0)->list);
    print_list(&head);
    
    free(ts);
}

TEST(test_list, list_replace)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("Before replace node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    printf ("After replace node:\n");
    list_replace(&(ts+0)->list, &(ts+2)->list);
    print_list(&head);
    
    free(ts);
}

TEST(test_list, list_replace_init)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("Before replace node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    printf ("After replace node:\n");
    list_replace(&(ts+0)->list, &(ts+2)->list);
    print_list(&head);
    
    free(ts);
}

TEST(test_list, list_move)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("Before move node:\n");
    printf ("Head1:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    print_list(&head1);
    printf ("Head2:\n");
    list_add_tail(&(ts+2)->list, &head2);
    print_list(&head2);

    printf ("After remove node:\n");
    list_move(&(ts+0)->list, &head2);
    
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);
    
    free(ts);
}

TEST(test_list, list_move_tail)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("Before move node:\n");
    printf ("Head1:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    print_list(&head1);
    printf ("Head2:\n");
    list_add_tail(&(ts+2)->list, &head2);
    print_list(&head2);

    printf ("After remove node:\n");
    list_move_tail(&(ts+0)->list, &head2);
    
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);
    
    free(ts);
}

TEST(test_list, list_is_last)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    list_add_tail(&(ts+2)->list, &head);
    print_list(&head);

    if (list_is_last(&(ts+0)->list, &head))
        printf ("(ts+0) is last!\n");
    else
        printf ("(ts+0) is not last!\n");
    
    if (list_is_last(&(ts+2)->list, &head))
        printf ("(ts+2) is last!\n");
    else
        printf ("(ts+2) is not last!\n");
    
    free(ts);
}

TEST(test_list, list_empty)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head);
    list_add_tail(&(ts+1)->list, &head);
    list_add_tail(&(ts+2)->list, &head);
    print_list(&head);

    if (list_empty(&head))
        printf ("head is empty!\n");
    else
        printf ("head is not empty!\n");
    
    free(ts);
}

TEST(test_list, list_is_singular)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head);
    printf ("after init node:\n");
    if (list_is_singular(&head))
        printf ("head is singular!\n");
    else
        printf ("head is not sungular!\n");
    
    printf ("add first node:\n");
    list_add_tail(&(ts+0)->list, &head);
    print_list(&head);

    if (list_is_singular(&head))
        printf ("head is singular!\n");
    else
        printf ("head is not sungular!\n");
    
    printf ("add second node:\n");
    list_add_tail(&(ts+1)->list, &head);
    print_list(&head);

    if (list_is_singular(&head))
        printf ("head is singular!\n");
    else
        printf ("head is not sungular!\n");
    
    free(ts);
}

TEST(test_list, list_cut_position)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    list_add_tail(&(ts+2)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);

    list_cut_position(&head2, &head1, &(ts+1)->list);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);

    free(ts);
}

TEST(test_list, list_splice)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    
    list_add_tail(&(ts+2)->list, &head2);
    printf ("Head2:\n");
    print_list(&head2);

    list_splice(&head2, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    /* print_list(&head2);  head2 是未知情况 */

    free(ts);
}

TEST(test_list, list_splice_tail)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    
    list_add_tail(&(ts+2)->list, &head2);
    printf ("Head2:\n");
    print_list(&head2);

    list_splice_tail(&head2, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    /* print_list(&head2);  head2 是未知情况 */

    free(ts);
}

TEST(test_list, list_splice_init)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    
    list_add_tail(&(ts+2)->list, &head2);
    printf ("Head2:\n");
    print_list(&head2);

    list_splice_init(&head2, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);         /* list_splice_init 的情况下, head2被初始化 */

    free(ts);
}

TEST(test_list, list_splice_tail_init)
{
    struct test_struct* ts = NULL;
    ts = (struct test_struct*)malloc(3 * sizeof(struct test_struct));
    init_test_struct(3, ts);
    
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    printf ("init node:\n");
    list_add_tail(&(ts+0)->list, &head1);
    list_add_tail(&(ts+1)->list, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    
    list_add_tail(&(ts+2)->list, &head2);
    printf ("Head2:\n");
    print_list(&head2);

    list_splice_tail_init(&head2, &head1);
    printf ("Head1:\n");
    print_list(&head1);
    printf ("Head2:\n");
    print_list(&head2);         /* list_splice_tail_init 的情况下, head2被初始化 */

    free(ts);
}

void print_list(struct list_head *h)
{
    struct test_struct *pos = NULL;
    
    list_for_each_entry(pos, h, list) {
        printf ("%d\n", pos->num);
    }
}

void init_test_struct(int n, struct test_struct* ts)
{
    int i;

    for(i = 0; i < n; i++){
        (ts+i)->num = i+1;
        INIT_LIST_HEAD(&(ts+i)->list);
    }
}

int main(int argc, char *argv[])
{
    return RUN_ALL_TESTS(argc, argv);
}

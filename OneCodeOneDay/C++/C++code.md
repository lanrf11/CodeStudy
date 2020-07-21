# 1.链表部分

## offer06 从尾到头打印链表
~~~cpp
/** 链表定义
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
~~~

~~~cpp
// 方法一：入栈、出栈
~~~
~~~Cpp 
// 方法二：遍历，vector翻转
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> ans;
        if(head == NULL){
            return {};
        }
        while(head != NULL){
            ans.push_back(head->val);
            head = head->next;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
~~~

~~~cpp 
// 方法三：递归
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> ans;
        if(head == NULL){
            return {};
        }
        helper(head, ans);
        return ans;
    }

    void helper(ListNode* head, vector<int>& ans){
        if(!head){
            return;
        }else{
            helper(head->next, ans);
            ans.push_back(head->val);
        }
    }
};
~~~

~~~cpp
// 自身递归
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        if(head == NULL){
            return {};
        }
        vector<int> ans = reversePrint(head->next);
        ans.push_back(head->val);
        return ans;
    }
};
~~~


## offer18 删除列表的结点

~~~cpp
// 方法一：设置头结点，不需要特殊考虑删除的是首节点
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* pre = new ListNode(-1);
        pre->next = head;
        ListNode* cur = pre;
        while(cur->next != NULL){
            if(cur->next->val == val){
                cur->next = cur->next->next;
                break;
            }
            cur = cur->next;
        }
        return pre->next;
    }
};
~~~

~~~Cpp 
// 方法二：分类讨论
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(head == NULL){
            return NULL;
        }
        if(head->val == val){
            return head->next;
        }
        ListNode* cur = head;
        while(cur->next != NULL){
            if(cur->next->val == val){
                cur->next = cur->next->next;
                break;
            }
            cur = cur->next;
        }
        return head;
    }
};
~~~

## offer22 链表中倒数第k个结点

~~~cpp
// 方法一：遍历一次统计结点数量，再遍历一次找到目标结点
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* cur = head;
        int count = 0;
        while(cur != NULL){
            cur = cur->next;
            count++;
        }
        cur = head;
        while(count-- > k){
            cur = cur->next;
        }
        return cur;
    }
};
~~~

~~~Cpp 
// 方法二：双指针
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* l = head, * r = head;
        while(k--){
            r = r->next;
        }
        while(r != NULL){
            l = l->next;
            r = r->next;
        }
        return l;
    }
};
~~~

## offer24 反转链表（☆）

~~~cpp
// 方法一：三结点
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = NULL, *cur = head, *nxt;
        while(cur != NULL){
            nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }
};
~~~

~~~Cpp 
// 方法二：递归
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL || head->next == NULL){
            return head;
        }
        ListNode* cur = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return cur;
    }
};
~~~

~~~Cpp 
// 方法三：
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL){
            return head;
        }
        ListNode *cur = head, *nxt = head->next;
        while(nxt != NULL){
            nxt = nxt->next;
            head->next->next = cur;
            cur = head->next;
            head->next = nxt;
        }
        return cur;
    }
};
~~~

## offer35 复杂链表的复制（偷懒了）

~~~cpp
// 方法一：unordered_map
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == NULL){
            return head;
        }
        unordered_map<Node*, Node*> nodemap;
        Node* cur = head;
        while(cur != NULL){
            Node* q = new Node(cur->val);
            nodemap[cur] = q;
            cur = cur->next;
        }
        cur = head;
        while(cur != NULL){
            Node* q = nodemap[cur];
            q->next = nodemap[cur->next];
            q->random = nodemap[cur->random];
            cur = cur->next;
        }
        return nodemap[head];
    }
};
~~~

## offer52 两个链表的第一个公共结点

~~~cpp
// 方法一：通过链表拼接消除差值，如果一个链表先走到尾部，则指向另一个链表。
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pa = headA, *pb = headB;
        while(pa != pb){
            pa = (pa != NULL) ? pa->next : headB;
            pb = (pb != NULL) ? pb->next : headA;
        }
        return pa;
    }
};
~~~

~~~cpp
// 方法二：1、先分别求出两个链表的长度；2、长度较长的链表先向前移动差值长度；3、两个链表一起移动，直到找到相等结点
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pa = headA, *pb = headB;
        int la = 0, lb = 0;
        while(pa != NULL || pb != NULL){
            if(pa != NULL){
                la++;
                pa = pa->next;
            }
            if(pb != NULL){
                lb++;
                pb = pb->next;
            }
        }
        pa = headA;
        pb = headB;
        if(la > lb){
            while(la-- > lb){
                pa = pa->next;
            }
        }else{
            while(la < lb--){
                pb = pb->next;
            }
        }
        while(pa != pb){
            pa = pa->next;
            pb = pb->next;
        }
        return pa;
    }
};
~~~

~~~cpp
// 方法三：1.遍历链表headA，并存入set中; 2.遍历headB，边遍历边在set中查找是否有相同元素。
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> nodeset;
        ListNode* p = headA;
        while(p != NULL){
            nodeset.insert(p);
            p = p->next;
        }
        p = headB;
        while(p != NULL){
            if(nodeset.count(p) > 0){
                break;
            }
            p = p->next;
        }
        return p;
    }
};
~~~

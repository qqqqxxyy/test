二刷题,按知识点总结
总结整理题目包含hot100和offer专项突击里面的题共219道
已重做9/219
1&0X:不在力扣上,属于手撕代码的部分

###### 二刷了的题目

*offerI:* (36)
    0I03, 0I04, 0I05, 0I06, 0I07, 0I09, 0I10-I, 0I10-II, 0I11, 0I12, 0I13, 0I14-I, 0I14-II, 0I15, 0I16, 0I17, 0I18, 0I20, 0I21, 0I22, 0I23, 0I24, 0I25, 0I26, 0I27, 0I28, 0I29, 0I32-1, 0I32-2, 0I32-3, 0I34, 0I36, 0I49, 0I60, 0I63, m0I13,

*offerII：*(20)
	0II04, 0II05, 0II06, 0II07, 0II08, 0II09, 0II10, 0II11, 0II12, 0II13, 0II14, 0II15, 0II16, 0II17, 0II18, 0II19, 0II20, 0II72, 0II68, 0II94

*hot100(总题号)：* (85道)
	001, 003, 004, 005, 008, 010, 011, 015, 017, 019, 020, 021, 022, 023, 025, 031, 032, 033, 034, 039, 042, 046, 047, 053, 054, 055, 062, 070, 072, 079, 088, 091, 092, 094, 096, 098, 101, 102, 103, 105, 113, 114, 121, 132, 134, 137, 139, 141, 142, 145, 146, 154, 155, 160, 165, 167, 169, 200, 206, 209, 215, 226, 232, 234, 236, 240, 263, 264, 279, 300, 343, 392, 316, 318, 402, 416, 468, 525, 543, 560, 583, 647, 713, 912, 1143, 1438

*值得再刷的题目*:
    0II17, {归并C}, 072, 042(O(1)空间), 581(O(1)空间), 525, 088(空O1,时OM+N,) 042, 143(翻转)

*可远观不可泄玩焉(总题号)*
	004, 321

#### 未整理刷题:
##### 07_17
手写strcat
```cpp
char* q_strcat(char*dest,char*source){
    char * ret=dest;
    assert(dest!=NULL);
    assert(source!=NULL);
    while(*dest!='\0'){
        dest++;
    }
    while(*source!='\0'){
        *(dest++)=*(source++);
    }*(dest)='\0';
    return ret;
}
int main(){
    char a[120]="nihao";
    char b[120]="buhao";
    // a="nihao";
    // b="buhao";
    q_strcat(a,b);
    for(auto i:a)cout<<i;
    return 0;
}
```

手写strcmp
```cpp
int q_strcmp(char*str1,char*str2){
    assert(str1!=NULL);
    assert(str2!=NULL);
    while( *(str1)!='\0' and *(str2)!='\0' and *(str1)==*(str2) ){
        str1++;str2++;  }
    if(*str1>*str2)return 1;
    if(*str1==*str2)return 0;
    if(*str1<*str2)return -1;
    return 0;
}
int main(){
    char a[120]="nihao";
    char b[120]="niz";
    // a="nihao";
    // b="buhao";
    cout<<q_strcmp(a,b)<<" "<<strcmp(a,b);
    return 0;
}
```
##### 07_05
cpp io
```cpp
int main(){
    int tmp,sum;
    while(cin>>tmp){
        sum+=tmp;
        if(cin.get()=='\n'){cout<<sum<<endl;sum=0;}
    }
    return 0;
}
```

```cpp
int main(){
    int tmp,sum;
    string line,tt;
    while(getline(cin,line,'\n')){
        stringstream ss (line);
        sum=0;
        while( ss>>tmp){
            sum+=tmp;
        }cout<<sum<<endl;
    }
    return 0;
}
```

#####
07_02
p12-74 (1h29'),本来没那么复杂的，其实只需要模拟就可以了，优先队列是唬人的。但借此机会复习了cpp的优先队列写法。以及三种定义优先级的方式1.自定义数据类型，在数据类型中定义operator<；2.定义compare；3.对于基本数据(int,double等)使用less;greater来定义

##### 06_24
264 {12'}+{0}+{0} + [掌握]
102 {16'55}+{0}+{0}+ [掌握]
236 {50'}+{0}+{5} 这道题的难点在于，如果用递归的方法，返回值是‘可能的’父节点，直到返回到根节点才能知道父节点是不是真的父节点。如果是公共父节点，只有两个情况，要么是在一侧，要么是在两侧。所以只用思考各个情况中最简单的模式就可以。

##### 06_18
(144)先序遍历不需要哈希的版本({10'}+{0}+{})
(有两种思路，一种是一直左左左，但每次左完都及时pop，一种是反序入栈) 
(094)中序遍历
后序遍历
?总结并复习对于vector,unordered_map的基本操作
0I27({3'}+{0}+{0})
0I28({7'14}+{0}+{0})
0I29(054) ({40'56}+{0}+{0})


##### 06_14
**023** 归并排序-链表版 (17'41)
**解析:**这次是用的归并排序解决的.  有几个点值得总结1.对于函数内创建的局部变量(LN),LN中的指针指向的地址不会随着局部变量的销毁而销毁(这个也符合常理).所以对于dummyhead的声明,最差的方法是new一个,因为如果不释放的话会增加很多空间复杂度.其次是声明局部变量,这个并不会影响算法整体.最极致的方法是声明一个类内的公共变量然后共用.(附上这一版本的代码)
```cpp
#define LN ListNode
class Solution {
public:
    LN dummyhd = LN();
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        LN * ans;
        int n = lists.size()-1;
        ans = merge(lists,0,n);
        return ans;
    }
    LN* merge(vector<ListNode*>& lists,int st,int ed){
        if(st>ed) return nullptr;
        if(st==ed) return lists[st];
        else{
            int mid = st+(ed-st)/2;
            LN * l1 = merge(lists,st,mid);
            LN * l2 = merge(lists,mid+1,ed);
            dummyhd.next=nullptr;
            LN *tmp=&dummyhd,*pt1=l1,*pt2=l2;
            while(pt1!=nullptr and pt2!=nullptr){
                if(pt1->val < pt2->val){tmp->next=pt1;tmp=tmp->next;pt1=pt1->next;tmp->next=nullptr;}
                else {tmp->next=pt2;tmp=tmp->next;pt2=pt2->next;tmp->next=nullptr;}     }
            if(pt1!=nullptr) tmp->next=pt1;
            else tmp->next=pt2;
            return dummyhd.next;   }
    }
```

前序遍历(144) ({45'14}+{0}+{5}) 迭代方法中,对于地址可以做哈希值完全没有印象了.不记得要记住哪些东西
```cpp 迭代版本
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;ans.reserve(105);
    vector<TN*> stack;stack.reserve(105);
    unordered_map<TN*, int> vis;
    if (root==nullptr)return ans;
    stack.push_back(root);ans.push_back(root->val);
    TN * pt;
    while(stack.size()){   
        while(stack.back()->left and vis.count(stack.back())==0){
            vis[stack.back()]=1; //记住遍历过左边的点
            pt=stack.back()->left;
            stack.push_back(pt);
            ans.push_back(pt->val); }
        pt=stack.back()->right;
        stack.pop_back();
        if(pt){
            stack.push_back(pt);
            ans.push_back(pt->val); }
    }
    return ans;
}
```

```cpp 递归版本
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        ans.reserve(105);
        fore(ans,root);
        return ans;
    }
    void fore(vector<int>& ans, TreeNode*root){
        if (root==nullptr) return;
        ans.push_back(root->val);
        fore(ans,root->left);
        fore(ans,root->right);
        return;
    }
};
```


##### 06_13
- [X] 归并排序-数组版


##### 06_11
**0I17打印从1到最大的n位数** 

**解析:**(太容易了)

**标签:**[容易]

```cpp
vector<int> printNumbers(int n) {
    vector<int>ans;
    int res = pow(n)-1;
    ans.reserve(res);
    for(int i=1;i<=res;i++)ans.push_back(i);
    return ans;}
int pow(int n){
int a = 1;
for (int i=1;i<=n;i++)a*=10;
return a;
}
```

**0I18删除链表的节点** ({5'50}+{0}+{0})
给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
返回删除后的链表的头节点。

**解析:**练习删除链表

**标签:**[容易]

```cpp
ListNode* deleteNode(ListNode* head, int val) {
    ListNode*tmp = head,*prev=NULL;
    while(tmp->val!=val){prev=tmp;tmp=tmp->next;}
    if (prev==NULL)return tmp->next;
    else{
        prev->next=tmp->next;
        tmp->next=NULL;
    }return head;
}
```

堆排序({42'}+{1})
**0I20表示数值的字符串** ({1h27'}+{2}+{0}) 垃圾题,复杂而没有意义.
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
数值（按顺序）可以分成以下几个部分：
若干空格;一个 小数 或者 整数;（可选）一个 'e' 或 'E' ，后面跟着一个 整数
若干空格;小数（按顺序）可以分成以下几个部分：
（可选）一个符号字符（'+' 或 '-'）
下述格式之一：
至少一位数字，后面跟着一个点 '.';至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字;一个点 '.' ，后面跟着至少一位数字
整数（按顺序）可以分成以下几个部分：
（可选）一个符号字符（'+' 或 '-'）
至少一位数字

**解析:**  垃圾题,复杂而没有意义.所谓有限状态机,无非是流程图,然后把每一个功能查拆分成尽可能原子的状态函数.

**标签:**[中等],[垃圾],[字符串]

```cpp
bool isNumber(string s) {
    s = DelSpace(s);
    int st,ed;st=0;ed=s.size()-1;
    int e = FindWord(s,st,ed,'e');
    if (e==-1) e = FindWord(s,st,ed,'E');

    if (e!=-1){
        int lst=0,led=e-1,rst=e+1,red=ed;
        bool lft=CheckS(s,lst,led) or CheckI(s,lst,led);
        bool rt = CheckI(s,rst,red);
        return lft and rt;
    }else{
        bool it = CheckS(s,st,ed) or CheckI(s,st,ed);
        return it;
    }
}
bool CheckI(string s,int st,int ed){
    if (s[st]=='+' or s[st]=='-')st++;
    return CheckNum(s,st,ed);
}
bool CheckS(string s,int st,int ed){
    if (s[st]=='+' or s[st]=='-')st++; 
    int pt = FindWord(s,st,ed,'.');
    if (pt==-1)return false;
    else {
        int lst=st,led=pt-1,rst=pt+1,red=ed;
        // cout<<lst<<" "<<led<<" "<<rst<<" "<<red<<endl;
        bool validaty = CheckNumNOL(s,lst,led) and CheckNumNOL(s,rst,red);   
        bool lengthy = (led-lst>-1) or (red-rst>-1);
        // cout<<validaty<<" "<<lengthy<<endl;
        return validaty and lengthy;}
}
string DelSpace(string s){
    int n = s.size();
    int sbj = n, ebj = -1;
    for(int i=0;i<=n-1;i++){if(s[i]!=' '){sbj=i;break;}}
    if(sbj==n)return "";
    for(int i=n-1;i>=sbj;i--){if (s[i]!=' '){ebj=i;break;}}
    int scale = ebj-sbj+1;
    s=s.substr(sbj,scale);
    return s;
}
bool CheckNumNOL(string s,int st,int ed){
    for(int i=st;i<=ed;i++){
        if (s[i]>'9' or s[i]<'0'){return false;}
    }return true;
}
bool CheckNum(string s,int st,int ed){
    if (st>ed)return false;
    
    for(int i=st;i<=ed;i++){
        if (s[i]>'9' or s[i]<'0'){return false;}
    }return true;
}
int FindWord(string s,int st,int ed,char word){
    int ans=-1;
    for(int i=st;i<=ed;i++){
        if(s[i]==word){
            ans=i;return ans;
        }}return ans;
}
```

**0I21调整数组顺序使奇数位于偶数前面** ({3'}+{1}+{0})
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。
**解析:**出错的一次是数组越界了.在while中也要判断数组不能越界.

**标签:**[数组],[容易]
```cpp
vector<int> exchange(vector<int>& nums) {
    int st=0,ed=nums.size()-1;
    while(st<ed){
        while(st<=nums.size()-1 and nums[st]%2==1)st++;
        while(ed>=0 and nums[ed]%2==0 )ed--;
        if(st<ed)swap(nums[st],nums[ed]);
    }return nums;
}
```

**0I22链表中倒数第k个节点** ({5'}+{0}+{0})
输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。
例如，一个链表有 6 个节点，从头节点开始，它们的值依次是 1、2、3、4、5、6。这个链表的倒数第 3 个节点是值为 4 的节点。

**解析:**没有想到用双指针的方法,双指针可以不用统计链表长度,但是在时间和空间上的复杂度是相同的.

**标签:**[链表],[双指针]

```cpp
ListNode* getKthFromEnd(ListNode* head, int k) {
    int ct=0;ListNode*tmp=head;
    while(tmp){
        ct+=1;
        tmp = tmp->next;}
    int num=ct-k+1;ct=0;
    // cout<<num<<" "<<ct;
    while(head){
        ct+=1;
        if (ct==num)return head;
        head=head->next;
    }return nullptr;
    //return head;
}
```

**0I24反转链表**
定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

**解析:**没啥好说的

**标签:**[链表],[容易]

```cpp
ListNode* reverseList(ListNode* head) {
    ListNode *prev=nullptr,*after=nullptr,*cur=head;
    while(cur){
        after=cur->next;
        cur->next = prev;
        prev = cur;
        cur = after;
    }return prev;
}
```

**0I25(021) 合并两个排序的链表** 基本套路


##### 06_09
**0I16数值的整数次方** ({13'}+{0}+{0}) 

**解析:**快速幂算法.注意两点:1.cpp没有类型自适应一说,要指定高精度. 2.对于int来说,是-2*23-2*31-1;因此对于合法负数取反之后可能是非法的.

**标签:**[偏易],[快速幂]

```cpp
double myPow(double x, int n) {
    bool neg=false;
    long long n0 = n;
    if (n0<0){neg=true;n0=-n0;}
    x = dfs(x,n0);
    if (neg) x = 1/x;
    return x;
}

double dfs(double x, long long n){
    if (n==0) return 1;
    if (n==1) return x;
    if(n%2==0) return dfs(x*x,n/2);
    else return dfs(x*x,n/2)*x;
}
```

##### 06_07
1.复习快速排序 
**0I14-II(343) 剪绳子II** ({17'16}+{0}+{0})
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m - 1] 。请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
2 <= n <= 1000
**解析：**因为数据规模的增加,动态规划需要O(n3)的复杂度，解决不了问题。但数学求解只需要O(n)（还可以通过快速幂优化成logn）,就是每根绳子都分成只有2，3组成的小段同时3的段尽可能多。这道题难不在代码上而是想不到。同时这种脑筋急转弯题目感觉也不太会考到。

**标签：**[数学]，[中等]，[掌握]

```cpp
int cuttingRope(int n) {
    int n_3=0,n_2=0;
    long long ans=1;
    if(n==2)return 1; if(n==3)return 2;

    if(n%3==0) n_3=n/3;
    if(n%3==1){n_3=n/3-1;n_2=2;}
    if(n%3==2){n_3=n/3;n_2=1;}
    // cout<<n_3<<" "<<n_2<<endl;
    for(int i=1;i<=n_3;i++){ans*=3;ans%=MOD;}
    for(int i=1;i<=n_2;i++){ans*=2;ans%=MOD;}
    return int(ans);
    // return int(1e9+8)%MOD;
}
```

**0I15 二进制中1的个数** ({3'}+{0}+{0}) [容易]
编写一个函数，输入是一个无符号整数（以二进制串的形式），返回其二进制表达式中数字位数为 '1' 的个数（也被称为 汉明重量).）。

**解析:**位运算,通过n&(n-1)移除最低为的1的特性统计1的个数.

**标签:**[容易],[位运算]

```cpp
int hammingWeight(uint32_t n) {
    int ct=0;
    while(n!=0){
        n = n&(n-1);
        ct+=1;
    }return ct;
}
```

##### 06_05
**0I11(154) 旋转数组** ({30'}+{0}+{5})
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
给你一个可能存在 重复 元素值的数组 numbers ，它原来是一个升序排列的数组，并按上述情形进行了一次旋转。请返回旋转数组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一次旋转，该数组的最小值为 1。  
注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。

**解析：**比较复杂的二分。比较方法是mid和left比较，如果mid>left,left=mid+1,如果mid\<left,right=mid；关键在于mid=left，因为有重复元素，无法判断，因此要做的是right-1.这种二分格式已经会了，但就是做题分析不出来。

**标签：**[偏难],[数组],[二分查找]

```cpp
int minArray(vector<int>& numbers) {
    int n = numbers.size()-1;
    int ans = erfen(numbers,0,n);
    return ans;
}
int erfen(vit&arr, int st, int ed){
    while(st<ed){
        int mid = (st+ed)/2;
        if (arr[mid]<arr[ed]){ed = mid;}
        else if (arr[mid]>arr[ed]){st = mid+1;}
        else ed-=1;
    }
    return arr[ed];
}
```

**0I12(079) 矩阵中的路径**({1d+30'34}+{5}+{1})
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
例如，在下面的 3×4 的矩阵中包含单词 "ABCCED"（单词中的字母已标出）。

**解析:**这道题是需要记忆化递归的.一方面递归如何把board用c传递(引用解决),一方面如何高效实现记忆化,都是之前不会的.python的时候可以用一个字典去记录,但是C语言的unorder map;unordered set默认不能对元组做哈希,所以比较麻烦还是.对于这道题来说,可以直接在原网格上标记\0进行记录,反而是代码\时间\空间最高效的一种方法.
记忆化一开始想复杂了,第二天判断ans的判断放进了外层循环查了半天 

**解析:**[偏难],[二维数组],[递归]

```cpp
class Solution {
public:
    int m,n,ln_wod;
    string wod;
    bool ans = false;
    vector<vector<char>>*bd;
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(),n=board[0].size();
        wod = word;
        ln_wod = word.size();
        bd = &board;
        for(int i=0;i<m;i++){
            for (int j = 0;j<n;j++){
                ans = dfs(i,j,0);
                if (ans==true){return true;}
            }
        }return false;
    }

    bool dfs(int i, int j, int sp){
        vector<vector<char>>& board = *bd;
        if (sp==ln_wod) return true;
        if(i<0 or i>=m or j<0 or j>=n) return false;
        if (board[i][j]!=wod[sp]) return false;
        
        char tmp = wod[sp];
        board[i][j]='\0';
        bool a = dfs(i-1,j,sp+1);
        bool b = dfs(i+1,j,sp+1);
        bool c = dfs(i,j-1,sp+1);
        bool d = dfs(i,j+1,sp+1);
        board[i][j] = tmp;
        // cout<<i<<" "<<j<<" "<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
        if(a or b or c or d) return true;
        else return false;
    }
};
```


**0I14-I(343)剪绳子**,({23'39}+{0}+{0})
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

**解析:**对于简单动态规划还是能做出来的.

**标签:**[动态规划],[偏易]

```cpp
    int cuttingRope(int n) {
        int ans = -1;
        int m = n; int i,j,k;
        vector<vector<int>>f(n+1,vector<int>(n+1,1));
        //初始化f[1][k]=k
        for(i=1;i<=n;i++){
            f[1][i]=i;
        }
        //i段,j米,第i段k米
        for(i=2;i<=n;i++){//最少2段,最多n段
            for (j=i;j<=n;j++){//最少i米,最多n米
                for (k=1;k<=j-i+1;k++){//最少1米最多j-i+1米
                    f[i][j] = max( f[i][j], f[i-1][j-k]*k );
                }if (f[i][j]>ans) ans = f[i][j];
            }
        }return ans;    }
```


冒泡排序 ({5'}+{0}+{0}) 
```cpp
vector<int> sortArray(vector<int>& nums) {
    int right,left,n;
    n = nums.size()-1;
    for(right=n-1;right>=0;right--){
        for(left=0;left<=right;left++){
            if(nums[left]>nums[left+1]){
                swap(nums[left],nums[left+1]);
            }
        }
    }return nums;}
```

选择排序 ({7'}+{0}+{0})
```cpp
vector<int> sortArray(vector<int>& nums) {
    int right,left,n,curm,curidx;
    n = nums.size()-1;
    for(right=n;right>=0;right--){
        curm = NIMAX;  curidx = -1;
        for(left=0;left<=right;left++){
            if (nums[left]>curm){curm=nums[left],curidx = left;}
        }swap(nums[right],nums[curidx]);
    }return nums;}
```

##### 06_04
**0I07(105)重建二叉树** ({1h53'}+{0}+{0}) 

**0I10-I 斐波那契数列**({8'04}+{0}+{0}) 
写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项（即 F(N)）。斐波那契数列的定义如下：
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

**解析:** 递推

**标签:**[数组],[递推],[容易]

```cpp
    int fib(int n) {
        int i,tmp,fir,sec;
        fir=0,sec=1;
        if (n==0) return fir;
        if (n==1) return sec;
        for (i=2;i<=n;i++){
            tmp = sec;
            sec+=fir;
            sec%=IMAX;
            fir = tmp;
        }return sec;
    }
```

0I10-II(70) ({4'08}+{0}+{0}) 和0I10-I没差别
一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

**解析:**递推,和I完全一样

**标签:**[容易]

```cpp
int numWays(int n) {
    int i,sp0,sp1,tmp;
    sp0=1,sp1=1;
    if (n==0)return sp0;
    if (n==1)return sp1;
    for (i=2;i<=n;i++){
        tmp = sp1;
        sp1+=sp0;
        sp1%=IMAX;
        sp0 = tmp;
    }return sp1;
}
```


##### 06_03
**0I03数组中重复的数字 **	({50'}+{0}+{0)
找出数组中重复的数字。
在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

**解析：**就是哈希，可以通过vector数组哈希或者unordered_map哈希的方式。回顾了vector的简单操作。非常简单，时间花在了 配环境+熟悉语言

**标签：**[容易]

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_map<int, bool> map;
        for(int num : nums) {
            if(map[num]) return num;
            map[num] = true;
        }
        return -1;
    }
};
```

**0I04(240) 二维数组中的查找** ({26'}+{2}+{0}) 
在一个 n * m 的二维数组中，每一行都按照从左到右 非递减 的顺序排序，每一列都按照从上到下 非递减 的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

**解析：**熟悉了二维数组以vector的表现形式以及操作。 题目本身没有难度。

**标签：**[容易]

```cpp
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int m,n;
        m = matrix.size()-1;
        if (m<0) return false;
        n = matrix[0].size()-1;
        if (n<0) return false;
        // cout<<m<<" "<<n<<endl;
        int i,j; i =0; j=n;
        while(true){
            bool valid = judge(i,j,m,n);
            if (not valid)return false;
            if (matrix[i][j]==target) return true;
            if (matrix[i][j]<target)i++;
            else j--;
        }
    }
    bool judge(int i ,int j,int m, int n){
        if (i<0 or i>m or j<0 or j>n)return false;
        else return true;
    }
};
```

**0I06从尾到头打印链表** ({8'16}+{0}+{0}) 
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

**解析：**回顾了链表的使用方法以及vector的另外一些使用方法。辅助栈，使用reserve预留空间节省时间。

**标签：**[容易]

```cpp
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> vec;
        vec.reserve(10005);
        while(head){
            vec.push_back(head->val);
            head = head->next;
        }
        vector<int> ans;
        int n = vec.size()-1;
        for(int i=n;i>=0;i--){
            ans.push_back(vec[i]);
        }
        return ans;
    }
};
```

##### 04_27
0II77

##### 04_26
**0II19最多删除一个字符得到回文**  ({20'}+{1}+{5}),
给定一个非空字符串 s，请判断如果 最多 从字符串中删除一个字符能否得到一个回文字符串。

**解析:**从外向里判断,如果从里向外,第一要考虑奇偶,第二如果不匹配了又要中心再过一遍.麻烦而且思考量达.从外向里就很简单.又是那种不难但忘记咋做就容易做错的面试坑题.

**标签:**[回文],[数组],[中等]

```cpp
class Solution {
public:
    bool flag=true;
    string m_s;
    int n;
    bool dfs(int i, int j){
        if (j<=i) {return true;}
        if (m_s[i]==m_s[j]) {return dfs(i+1,j-1);}
        else{
            if (flag==false) return false;
            else {flag = false; return ( dfs(i+1,j) or dfs(i,j-1) );} }
    }
    bool validPalindrome(string s) {
        m_s=s;
        n = s.size();
        return dfs(0,n-1);
    }
};
```

**0II20回文子字符串的个数**({5'}+{0})
给定一个字符串 s ，请计算这个字符串中有多少个回文子字符串。
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

**解析:**对每个元素进行向外扩展,做过太多遍了.

**标签:**[数组],[递推],[容易]

```cpp
class Solution {
public:
    int n;
    int i,j,ct=0;
    string m_s;
    int countSubstrings(string s) {
        m_s = s;
        n = m_s.size();
        for (i =0;i<n;i++){
            dfs(i,i);
            dfs(i,i+1);}            
        return ct;
    }

    void dfs(int i,int j){
        if (i<0 or j>n-1){return ;}
        if (m_s[i]==m_s[j]){
            ct+=1; dfs(i-1,j+1);
        }else{return ;}
    }

};
```

##### 04_19
&1&02_912;

##### 04_18
offerII15/16/17
**offer0I15字符串中的所有变位词** *({22'15}+{0}) CPP* 
给定两个字符串 s 和 p，找到 s 中所有 p 的 变位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
变位词 指字母相同，但排列不同的字符串。

**解析:**0I14增加了点难度,找到所有变位词,就输入不停的增减即可,写得很快但有个bug查了好几分钟:我忘了指针到哈希表键的转换.

**标签:**[数组],[字符串],[遍历],[偏易]

```cpp
class Solution {
public:
    int hmap[26];
    int i,j,k,ct,np,ns,st,ed,posed,posst;
    vector<int> ans;
    vector<int> findAnagrams(string s, string p) {
        memset(hmap,0,sizeof(hmap));
        np=p.size();ns=s.size();
        for(auto i:p){   int tmp=int(i)-int('a'); hmap[tmp]+=1;    }
        st=0;ed=0;ct=np;
        for(ed=0;ed<ns;ed++){
            posed = int(s[ed])-int('a');
            hmap[posed]-=1;ct-=1;
            while(hmap[posed]<0){
                posst=int(s[st])-int('a');
                hmap[posst]+=1;
                st++;ct++;}
            if(ct==0){ans.push_back(st);} }
        return ans;
    }
};
```

**offer0I16不含重复字符的最长子字符串** *({6'55}+{1}) CPP* 

**解析:**和15,14的不同之处在于是字符而不是子母了,无非是哈希数组开大一点.

**标签:**[数组],[偏易]

```cpp
class Solution {
public:
    int hmap[10000];
    int lft,n,rt,i,j,k,ans=0,posrt,poslft;
    int lengthOfLongestSubstring(string s) {
        memset(hmap,0,sizeof(hmap));
        lft=0;n=s.size();
        for(rt=0;rt<n;rt++){
            posrt= s[rt];
            hmap[posrt]++;
            while(hmap[posrt]>1){
                poslft= s[lft];
                hmap[poslft]--;
                lft++;            }
            ans = max(ans,rt-lft+1);
        }
        return ans;
    }
};
```

**0II17含有所有字符的最短字符串** *(47'59+{1}) CPP*

**解析:**应该先找到第一个合法的字符串,然后往下遍历找最短.我把这两个和在一起,结果必须要判断每次归零是否是该子母初次归零,增加了思考量.

**标签:**[数组],[中等]

```cpp
#define IMAX 1000000
class Solution {
public:
    int hmap[130],compete[130];
    int i,j,k,ctype=0,ns,nt,st,ed,ast=0,aed=IMAX,pst,ped;
    string minWindow(string s, string t) {
        memset(hmap,0,sizeof(hmap));
        memset(compete,0,sizeof(compete));
        for (auto i: t){
            hmap[i]++;
            compete[i]=1;
            if (hmap[i]==1) ctype++;}
        st=0;ns=s.size();nt=t.size();
        for(ed=0;ed<ns;ed++){
            pst=s[st];ped=s[ed];
            hmap[ped]--;
            while(hmap[pst]<0){
                hmap[pst]++;st++;pst = s[st];
            }
            if(hmap[ped]==0 and compete[ped]==1){
                compete[ped]=0;ctype--; }
            if (ctype==0){
                if ( (aed-ast+1) > (ed-st+1) ) aed=ed,ast=st; 
                }
        }
        string ans;
        if (aed==IMAX) ans="";
        else ans=s.substr(ast,aed-ast+1);
        return ans;
    }
};
```


##### 04_17
**offer0I13二维子矩阵的和** *({18'16}+{0) CPP*
给定一个二维矩阵 matrix，以下类型的多个请求：
    计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1) ，右下角为 (row2, col2) 。
实现 NumMatrix 类：
    NumMatrix(int[][] matrix) 给定整数矩阵 matrix 进行初始化
    int sumRegion(int row1, int col1, int row2, int col2) 返回左上角 (row1, col1) 、右下角 (row2, col2) 的子矩阵的元素总和。

**解析:**二维前缀和,先通过On2预处理得到前缀矩阵,之后每次查询只用消耗O1的时间

**标签:**[前缀和],[偏易]

```CPP
#include <bits/stdc++.h>
#define IMAX 205
int ans,m,n;
int i,j,k;
int sumvec[IMAX][IMAX];
vector<vector<int>>mtx;
class NumMatrix {
public:

    NumMatrix(vector<vector<int>>& matrix) {
        mtx = matrix;
        m = mtx.size();n = mtx[0].size();
        for (i=m-1;i>=0;i--){
            for(j=n-1;j>=0;j--){
                sumvec[i][j]=mtx[i][j]+sumvec[i][j+1]+\
                             sumvec[i+1][j]-sumvec[i+1][j+1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        ans = sumvec[row1][col1]+sumvec[row2+1][col2+1]-\
              sumvec[row1][col2+1]-sumvec[row2+1][col1];
        return ans;
    }
};

```

**offer0I14字符串中的变位词** *({38'}+{0) CPP*
给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的某个变位词。
换句话说，第一个字符串的排列之一是第二个字符串的 子串 。

**解析:**变位词即和次序没关系,用一个数组记录子母出现次数,然后对s2遍历即可.耗时长是语法问题.

**标签:**[数组],[遍历],[容易]

```cpp
int i,j,k,ct,st,ed,tmp,tmpst,n,m;
char lt;
int wordmap[26];
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        memset(wordmap,0,sizeof(wordmap));
        for (auto lt:s1){    tmp = int(lt)-int('a'); wordmap[tmp]+=1;     }
        n=s1.size();m=s2.size();
        st=0;ed=-1;
        while(ed<m-1){
            // cout<<st<<" "<<ed<<endl;
            ed+=1;tmp = int(s2[ed])-int('a');
            wordmap[tmp]-=1;
            while(wordmap[tmp]<0){
                tmpst=int(s2[st])-int('a');
                wordmap[tmpst]+=1;st++;}
            if (ed-st+1==n) return true;
        }return false;
    }
};
```


##### 04_16
**offer0I12左右两边子数组的和相等** *({27'38}+{0} CPP)* 空间不是O1的.
给你一个整数数组 nums ，请计算数组的 中心下标 。
数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。
如果中心下标位于数组最左端，那么左侧数之和视为 0 ，因为在下标的左侧不存在元素。这一点对于中心下标位于数组最右端同样适用。
如果数组有多个中心下标，应该返回 最靠近左边 的那一个。如果数组不存在中心下标，返回 -1 。

**解析:**数组+针滑动题.注意指针所处元素不计入.CPP中通过?:三元操作符可以写得更简洁.

**标签:**[数组],[容易],[指针]

```cpp
#include <bits/stdc++.h>
//#include <vector>
using namespace std;
vector<int> prevec(10000,5);
class Solution {
public:
int n,i,j,k,sum=0;
int left,right,ans=-1;
    int pivotIndex(vector<int>& nums) {
        n = nums.size();
        for(i=0;i<n;i++){
            sum+=nums[i];
            prevec[i]=sum;}
        for(i=0;i<n;i++){
            left= (i>0?prevec[i-1]:0);
            right = prevec[n-1] - prevec[i];
            if (left==right){ans = i;break;}}
        return ans;
    }
};
```

##### 04_15
手撕线段树

##### 04_13
美团第五题;找一些递归的题目来做

##### 04_11
堆排序 62',
后序遍历二叉树 52'38
循环链表(hot142); 31'38

##### 04_10
学习线段树的C++编写;
先023,
**P11_39塔子哥的收藏夹**
[美团],[04_01],[3/5]
```
塔子哥是一个热爱收藏的年轻人，他喜欢收集各种有趣的物品，例如邮票、硬币、瓶盖等等。他的收藏品越来越多，于是他决定为自己在收藏架上建了一排 nn 个收藏夹，分别编号为 1,2,3…n1,2,3…n。这样，他就可以更好地组织和展示自己的收藏品了。

塔子哥有些时候会突发奇想改变某一个收藏美里的内容，例如从中拿入、拿出一些藏品，这些的操作会改变塔子哥对这个收藏夹的欣赏程度，我们记编号为 ii 的收藏夹，塔子哥对其的欣赏程度为 aiai​ 。塔子哥在休息时间经常会欣赏连续编号的收藏夹，例如编号为 L,L+1,L+2,...,R−1,RL,L+1,L+2,...,R−1,R 的这些收藏夹，他能从中获得的满足感为这些收藏失的欣赏程度之和，即 ∑i=LRai∑i=LR​ai​ 。

塔子哥想在欣赏之前提前估算自己能得到的满足感，想知道如果他选择编号区间为 [L,R][L,R] 的收藏夹，能给他带来的满足感是多少。但是塔子哥不想自己计算，所以他想你帮他计算一下，然后告诉他。
输入描述:
第一行两个整数 nn 和 mm ，表示塔子哥的收藏夹数量和塔子哥的操作数量。初始时刻收藏夹都是空的，也即 ai=0ai​=0 （ i∈[1,n]i∈[1,n] ）
第二行 mm 个整数 op1,op2,…,opmop1​,op2​,…,opm​ 。
第三行 mm 个整数 x1,x2,…,xmx1​,x2​,…,xm​ 。
第四行 mm 个整数 y1,y2,…,ymy1​,y2​,…,ym​ ，这些共同表示了 mm 次操作，对于第 ii 次操作， opi=0opi​=0 时表示为一次收藏夹更新操作，会将 xixi​ 位置的收藏夹欣赏程度更新为 yiyi​ ，即 axi=yiaxi​​=yi​ ； opi=1opi​=1 时表示为一次查询操作，表示如果塔子哥欣赏编号在区间 [xi,yi][xi​,yi​] 的收藏夹，能获得的满足感是多少，也即 ∑j=xiyiaj∑j=xi​yi​​aj​ 。

对于所有的数据， 1≤n,m≤50000,opi∈[0,1]1≤n,m≤50000,opi​∈[0,1] ，当 opi=0opi​=0 时， 1≤xi≤n,0≤yi≤100001≤xi​≤n,0≤yi​≤10000 ；当 opi=1opi​=1 时， 1≤xi≤yi≤n1≤xi​≤yi​≤n ，保证至少有一次 opi=1opi​=1 的操作。
```
**解析:**通过数据规模,前缀和遍历不能通过全部样例(修改操作复杂度为ON).是线段树模板题.而且是线段树最简单的版本,只涉及到区间查找而不涉及区间查找.但是要注意的是,单点修改要修改到叶子节点,按照定理只需要logn.但区间查询是如果上层能覆盖下层信息,就不要查找下层了,不然会退化成ON的修改复杂度.

**标签:**[线段树],[中等]


##### 04_06
11_39(线段树没搞定), ~~11_40~~, 11_41(先)
/~~042~~
复现一些基本算法操作:
1.推排序 2.后序遍历二叉树 3.循环链表 (后后)


##### 04_05
1.早起(8:00) 2.来了先复习前一天的知识.  ~~3.把百度第三题做了~~ 4.再把 
/072/042做了
美团P~~11_37,11_38~~,

**P11_34塔子的有根树**  * 82' cpp *
[百度],[03_28],[3/3]

```cpp
#include <bits/stdc++.h>
using namespace std;
#define V vector<int>
#define VV vector<vector<int>>
#define N n+5
int n;
VV edge,weight,multi,ans;
V ans_zero;
void read_weight();
void read_edge();
void read_multi();
int get(int num, int s);
void PrintVV(const VV & a);
void dfs(int rt, int fa);
int main()
{
    cin>>n;
    edge = VV(N);weight=VV(N);multi=VV(N,{0,0});ans=VV(N,{0,0});ans_zero=V(N,0);
    read_weight();
    read_edge();
    read_multi();
    dfs(1,-1);
    for(int i=1;i<=n;i++){cout<<ans_zero[i]<<" ";}cout<<endl;

}
void dfs(int rt, int fa){
    //继承之前的乘法
    if (fa!=-1){multi[rt][0]+=multi[fa][0];multi[rt][1]+=multi[fa][1];}
    ans[rt][0]+=weight[rt][0];ans[rt][1]+=weight[rt][1];
    ans[rt][0]+=multi[rt][0];ans[rt][1]+=multi[rt][1];
    for (auto cld:edge[rt]){
        if (cld==fa){ continue;}
        dfs(cld,rt);
        //和子树的结果相乘
        ans[rt][0]+=ans[cld][0],ans[rt][1]+=ans[cld][1];
    }ans_zero[rt]=min(ans[rt][0],ans[rt][1]);
}

void PrintVV(const VV & a){
    for (auto i : a){
        for (auto j:i){cout<<j<<" ";}cout<<endl;
    }
}
void read_weight(){
    int wt,n2,n5;
    for(int i=0;i<n;i++){
        cin>>wt;
        n2=get(wt,2);n5=get(wt,5);
        weight[i+1]={n2,n5};
    }
}
void read_edge(){
    int st,ed;
    for (int i=0;i<n-1;i++){
        cin>>st>>ed;
        edge[st].push_back(ed);
        edge[ed].push_back(st);}
}
void read_multi(){
    int q,pt,mul;int n2,n5;
    cin>>q;
    for (int i=0;i<q;i++){
        cin>>pt>>mul;
        n2=get(mul,2);n5=get(mul,5);
        multi[pt][0]+=n2;multi[pt][1]+=n5;
    }
}
int get(int num, int s){
    int ans = 0;
    while(num%s==0 and num>0){
        num/=s;
        ans+=1;
    }return ans;
}
```

##### 04_04
**207课程表** * cpp {70'} *
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
    例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

**解析:**拓扑排序,dfs or bfs

**标签:**[深度优先搜索],[中等]

```cpp
class Solution {
public:
    int m_ct=0;
    vector<int>m_du;
    vector<int>m_visit;
    vector< vector<int> >edge;
    void dfs(int cur){
        m_visit[cur]=1;m_ct+=1;
        for (int pt: edge[cur]){
            m_du[pt]-=1;
            if (m_du[pt]==0 and m_visit[pt]==0){
                dfs(pt);} }}
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n=numCourses,i,cur;
        m_du=vector<int>(n+1,0);m_visit=vector<int>(n+1,0);
        vector<int>m_null;
        edge = vector<vector<int>>(n+1);
        vector<vector<int>>& pre = prerequisites;
        for (const auto & pt: pre){
            int ed=pt[0],st = pt[1];
            edge[st].push_back(ed);
            m_du[ed]+=1;}
        for (i=0;i<n;i++){
            if (m_du[i]==0 and m_visit[i]==0){
                dfs(i);}}
        if (m_ct==n){return true;}
        else{return false;}}};
```

124 * cpp {15'39+{0}+{0}}*

##### 04_03

[X] 腾讯的两套题整理(先)
笔试题,当你估计python代码超过50行或者CPP代码超过70行的时候,很可能是你的思路有问题了.笔试不可能出代码过于复杂的题目.很可能是有更简单的处理方式没有想到.

**P11_26**
[腾讯],[03_26],[5/5]
塔子哥有一个长度为n的整数序列a。他想玩一个游戏，从这个序列中删掉一些数，使得剩下的数的最大公约数等于k。
问塔子哥有多少种删除的方案。如果答案太大，就把它对 10e9+7 取模。
最大公约数：指两个或多个整数公有约数中最大的一个。

**解析:** 难点:1.想到只有m*k这样的数才有可能不被删除(抽象,简化问题,我也想到了). 2.如果计算所有mk的数的组合,得到是公约数为mk(m>=1)的可能性. 3.通过动态规划的方式,公约数等于mk的组合 =公约数大于等于mk组合(可以直接计算到)- 公约数等于(2m)k-3mk-...nmk(通过前面的状态的到). 构建出一个序列动归. 4.很多细节问题,比如幂运算要通过快速密才不会报超时. 压轴题,很难.
最终我的python代码虽然思路对了,但是也没有通过样例(一个点没过).我想用字典存数据,这样应该更快一点,但是显然代码有问题.

**标签:**[问题分析],[动态规划]

**P11_25子数组异或和**
[腾讯],[03_26],[4/5].

塔子哥有一个正整数数组 A ，他想玩一个游戏，找出数组中有多少个连续的子数组，满足以下条件： 子数组中的所有数字相乘的结果和相异或的结果相等。
每有一个满足条件的子数组即得一分，问塔子哥最多能得到多少分？
一个数组的子数组指数组中非空的一段连续数字。

**解析:**有几个难点:1.想到异或结果等于相乘结果<=>偶数个1+一个额外的数.(这是问题的第一步抽象,这一部我往往能想到) 2.想到利用前缀和数组记录连续的1左边次数和右边次数. 3.想到1和非1的判断标准是不同的. 这道题是ON复杂度,只需要一个遍历.如果思路清楚的话,在考场上是有可能写出来的; 如何想到:从数具规模判断最多NlogN. 不存在树结构等复杂的数据结构.  

**标签:**[问题分析],[前缀和],[一次遍历]

##### 04_02

快速排序,

##### 03_31

三道力扣题:
[X]后序遍历二叉树(145) * 18'54+{0} * ,
022 *7'02+{0}*,
264 *14'05+{0}*

##### 03_30

目前,之前投的公司的笔试都做完了.接下来要对这些 笔试 全部进行整理 .除了亚马逊的笔试过于简单以外. *阿里(03_22) X 找不到题目 ,勾 腾讯(03_26),百度(03_28),拼多多(03_30) X 找不到题目* 都有值得总结的题目(也就是没做出来的题目.)首先总结这四家的.然后总结之前做的,特别是没做出来的题目. 但是也不能过于纠结.如果不是套路类型的题,下面花2个小时搞明白估计临场还是做不出来.不宜纠结于单一问题.

##### 03_28

**10_47灯塔,拼多多 (失败)**
数据规模导致python只能过两个样例.同时,只想到二分还不够,要有对整数和小数的讨论.
**10_87 小美抓敌人 (94%)(有C标答)**

##### 03_27

**10_79 字符串重排**
**10_80 构造回文串**
**10_23 删除游戏**

**10_81 树上的连同块**
**10_76 多多进行团建 (失败)**
**10_24 01反转 (非常简单)**

**11_12 捡西瓜丢芝麻 (失败)**

##### 03_26

腾讯音乐三道题,就独立做出来了签到题
**11_06划分字符串**,
**11_07小红的签到题**(签到题),
**11_08调整字符串**

**10_65:米哈游:树的染色**

**10_76:拼多多:多多进行团建**

##### 03_25

百度 10_70-10_72 3ak
python格式化输出
转c++首先要学习格式化输出,包括:
保留有效数字,取整,取模

10_44 (60')
10_45 10_46 10_47
**P10_45:PDD 爬山** *32'*
题目内容
多多村山清水秀，景色宜人，多多君周末经常约朋友一起登山。
多多君登山时每一步可以选择向上爬一个台阶或者多个台阶，如果登山时选择的台阶不同，则为一种爬山方案。
多多君想知道，多多村的每座山各有多少种不同的爬山方案(输出结果对 109+7109+7 取模)。
输入描述
第一行，三个整数 NN 、 PP 和 KK 分别代表山的个数 NN ，多多日一次最高能爬的高度 PP 以及多多君一次最多能跨越的台阶数 KK 。
( 1≤N≤101≤N≤10 ， 1≤P≤1,0001≤P≤1,000 ， 1≤K≤1,0001≤K≤1,000 )
接下来 NN 行，每行的第一个整数 MiMi 表示第 ii 座山一共有 MiMi 个台阶，接下来有 MiMi 个整数，分别表示每个台阶的高度 HjHj
( 1≤Mi≤10,000,1≤Hj≤1,0001≤Mi≤10,000,1≤Hj≤1,000)。
输出描述
输出 NN 行，每行一个整数，表示第 ii 座山多多君可以选择的登山方案数目。

**分析:**通过数据量判断至少双重循环(或者NP),最终确定二维动归.

```python
N,d_h,d_n = [int(x) for x in input().split()]
for circle in range(N):
    inpu = [int(x) for x in input().split()]
    n = inpu[0]
    arr = inpu[1:]
    flag = 1
    dp = [0]*n
    #判断山合法
    for i in range(n):
        if arr[i]>d_h: 
            print(0)
            flag=0
            break
    if flag == 0:
        continue
    else:
        #初始化
        st_h,st_n=0,-1
        while(True):
            st_n+=1
            st_h+=arr[st_n]
            if st_h<d_h and st_n<d_n:
                dp[st_n]=1
            else:
                break
        for i in range(1,n):
            cur_h=0
            for j in range(i,0,-1):
                if i-j+1>d_n: break
                cur_h+=arr[j]
                if cur_h>d_h: break
                dp[i]+=dp[j-1]
                if dp[i]>=10**9+7:
                    dp[i]=dp[i]%(10**9+7)
        print(dp[n-1])
```

**P10_44:PDD 投喂猫** *60'*
题目内容
多多君生活在美丽的多多村，平常的休息时间，多多君会在家附近散步，顺便会投喂经过遇到的小猫咪们。
多多村共有 NN 个街区(分别编号 11 ~ NN ，多多君住在 11 号区)，以及有 N−1N−1 条道路，保证街区两两之间相互连通，且只有唯一一条通路， 且已知第 ii 个街区有 AiAi 只猫猫。
多多君对散步路线有以下要求:
    散步路线中不能重复经过某个街区
    只能带不超过 MM 份猫粮出门( 11 份猫粮只能投喂 11 只猫咪)
    为了保持和小猫咪们的友好关系，若要经过某个街区则要投喂其中所有的猫咪(^. w .^)
多多君想知道，应当如何选择散步路线，使得能投喂到最多数量的街区，且需要的猫粮数量最少。
输入描述
第一行，两个整数 NN 和 MM ，分别表示多多村街区的数量，和准备带出门的猫粮的份数( 1≤N≤50,0001≤N≤50,000 ， 0≤M≤5,000,0000≤M≤5,000,000 )
第二行，共 NN 个整数，其中第 ii 个整数 AiAi 表示第 ii 个街区的猫猫的数量。( 0≤Ai≤1000≤Ai≤100 )
接下来 N−1N−1 行，每行两个整数 XX 和 YY ，表示编号 XX 和 YY 的街区之间存在一条道路。( 1≤X,Y≤N1≤X,Y≤N )
输出描述
共一行，两个整数，分别表示：能投喂最多数量的街区，以及在此情况下需要最少多少猫粮。

**解析:**正确理解题目内容从而建模是解决问题的第一步也是关键一步.这道题1.没有规定给出道路的从左到右的顺序,是双联通而不是单联通.所以表记录也应该记录的是双向道路.2.没有规定从出发点能一条路径不重复的访问所有点,所以不能遍历而是要用搜索. 包括上午做的百度,包括阿里,包括这道题.有至少一半的题目是因为太着急了,光想着快,导致第一次没有能够正确理解题目含义而导致的解法错误(或者只解决了部分点.).在最开始必须要**静下心来正确建模.**

```python
N,M = [int(x) for x in input().split()]

arr = [1]
tarr = [int(x) for x in input().split()]
for elem in tarr:
    arr.append(elem)
from collections import defaultdict
hmap = defaultdict(list)
for i in range(N-1):
    st,ed = [int(x) for x in input().split()]
    hmap[st].append(ed)
    hmap[ed].append(st)
hmap[0].append(1) #初始值
max_b,min_f=-1,M+1
vis=set()
def dfs(cur_b,vis,c_food,ct):
    nex_bs = hmap[cur_b]
    for nex_b in nex_bs:
        if nex_b in vis:continue
        else:
            vis.add(nex_b)
            global N,M,max_b,min_f
            nex_food = c_food+arr[nex_b]
            if nex_food > M: continue
            else:
                ct+=1
                if max_b<ct or (max_b==ct and min_f>nex_food):
                    max_b,min_f = ct,nex_food
                dfs(nex_b,vis,nex_food,ct)
                ct-=1


dfs(0,vis,0,0)
if max_b==-1:
    print(0,0)
else:
    print(max_b,min_f)
```

##### 03_24

054 *38'14+{0}*
由于一开始每次拐弯只约束了一个条件,导致总是有溢出的情况.在时间复杂度没有指数增长的前提下,请不要吝啬增加额外的约束; 如果每次移动指定个格子,则可以不用判断四个边界,但似需要确定走的路长度.都差不多.

316 *22'01+{1}*
没考虑到字典序的贪心. 思路:去重,一个很显然思路就是用vis数组记录,访问过的不再访问.字典序小,则小字母尽可能在前,此时很显然的就可以想到如果后面还有相同的元素,把较大元素替换成小子母可以提高字典序.

##### 03_23

318 *37'48+{0}+{2.5}*
第二次做比第一次做花的时间还长.从'单词含有公共字母'这一点想到要用位运算.位运算一般都是用来快速比较两个数/两个单词是否一样(从26*26变成了1*1的时间复杂度.)

525 *37'28+{0}+{5}*

200 *16'24+{1}*

088 *24'22+{0}*X 思路:ON2时间的问题再于,从前往后数,不能确定位置造成一个点多次挪动.而从后往前数,则每次都可以确定一个位置,减少了挪动次数.

**1&05python中常用的三个容器**

```python
#一些python中的容器
#堆,队列,defaultdict
#defaultdict
from collections import defaultdict
hmap = defaultdict(int)
print(hmap[0])

#队列
from collections import deque
que =deque([1,2,3])
que.appendleft(1)
que.pop()
print(que)

#堆 操作最为繁琐
#重点有heapify(hp),heappop(hp),heappush(hp,num)
import heapq
hp = [4,3,2,1]
heapq.heapify(hp)
print(hp[0])

heapq.heappop(hp)
heapq.heappush(hp,-1)
print(hp)

bhp = [-x for x in hp]
heapq.heapify(bhp)
print(bhp[0]*(-1))
```

##### 03_22

581 *26'04+{1}*(这次用了单调栈,但发现双指针可以实现O(1)的空间复杂度)

##### 03_21

I/O练习;  098(递归) *15'55+{1}* , 105 *22'12+{0}* *但差一点完美,如果外面用哈希记录中序的数字和下标对应,则递归中可以避免每次都要对中序列表的一个子集进行搜索,大幅减少时间消耗.* ,033 *24'11+{1}* 总之就是分类要分清楚,

##### 03_20

132 *19'40+{0}*, 279, *9'09+{0}*, 143 *25'01+{0}+{2.5}*, 042 *26'14+{0}*(空间又没有优化)

##### 03_17

1&04 二叉树三序遍历,
前序 *2'13+{0} and 17'07+{1}*
中序 *2'13+{0} and 10'13+{0}*
后序 *0'53+{0} and 15'02+{0}*
三个序列的递推都重新想了一次,并且先序和后序和最优代码差距还有点大,

```python
#好久没做了,一些错误分析
#先序递推:
def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
    ans = []
    if not root: return ans
    from collections import deque
    que = deque()#从这里就开始错
    que.append(root)
    while(que):
        cur = que.popleft()
        ans.append(cur.val)
        if cur.left: que.append(cur.left)
        if cur.right: que.append(cur.right)
    return ans
#这个最大的错误是用了队列,栈每个while循环入栈新元素巧妙的保证了'递归'性质;记住,遍历都用栈.先序遍历不用vis

```

##### 03_16

392-进接版 *15'37+{0}* ,459 *42'04+{oo}+{5}* ,1143 *12'41+{0}*
**459**
这是人能想出来的?kmp背我也懒得背,碰到了就认倒霉.

**1143** *12'41+{0}*
给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
    例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

**解析:**进一步简化版的字符串操作.最大难度可能是想不到是动态规划,但因为做过编辑距离,删除操作.这个想到是动归的话状态方程就比较好写了.

**标签:**[动态规划],[字符串],[中等]

```python
def longestCommonSubsequence(self, text1: str, text2: str) -> int:
    m,n = len(text1),len(text2)
    dp = [[0 for x in range(n+1)] for x in range(m+1)]
    for i in range(1,m+1):
        for j in range(1,n+1):
            wi,wj = text1[i-1],text2[j-1]
            if wi==wj:
                dp[i][j]=dp[i-1][j-1]+1
            else:
                dp[i][j] = dp[i-1][j] if dp[i-1][j]>= dp[i][j-1] else dp[i][j-1]
    return dp[m][n]
```

##### 03_15

392 *7'47+{0}* ,028 *28'41+{0}*

- [X] 复习堆排序,

**hot583两个字符串的删除操作**  *(03_15)28'41+{0}*
给定两个单词 word1 和 word2 ，返回使得 word1 和  word2 相同所需的最小步数。
每步 可以删除任意一个字符串中的一个字符。

**解析:**如果不是做了编辑距离,是很难想出来这道题.我判断了(i-1)(j-1)和(i-1)(j),(i)(j-1)之间的最小值,但其实后面一定大于前面,但相差1最多就多1.所以可以先判断前者,在判断后两者.但是时间复杂度一样的,而且我写的思考代价更小一些.字符串的动态规划题真的不太容易.

**标签:**[字符串],[动态规划],[偏难]

```python
def minDistance(self, word1: str, word2: str) -> int:
    '''另一个版本的编辑距离,甚至不是简化版,就是变种
    这里有一个逻辑连接是dp[ℹ-1][j-1]和dp[ℹ-1][j]最多相差1
    所以如果dp[i-1][j-1]+2必<=dp[i-1][j]+1
    '''
    m,n = len(word1),len(word2)
    dp = [ [0 for x in range(n+1)] for x in range(m+1) ]
    for i in range(n+1):
        dp[0][i]=i
    for j in range(m+1):
        dp[j][0]=j

    for i in range(1,m+1):
        for j in range(1,n+1):
            t1,t2=i-1,j-1
            if word1[t1]==word2[t2]:
                a = dp[i-1][j-1]
            else:
                a = dp[i-1][j-1]+2
      
            b =  dp[i-1][j]+1
            c = dp[i][j-1]+1

            dp[i][j]=min(a,b,c)

    return dp[m][n]
```

**hot392判断子序列**  *7'47+{0}*
给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

进阶：
如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

**解析:**就是双指针的解法,不过我写的不像双指针了.是一种贪心的思想,当s中的某一字符在t中多次出现时,越早抵消掉月号.但是进阶版,有10亿个s就不容易了. *03_16*进接版分析:因为有很多个s,而t又比较大,如果10亿乘上一个t长度的复杂度是负担不起的,所以对t做一个哈希表,记录每隔位置到下一个字母的最近位置.这样是10亿乘s的平均长度,可以接受.但要注意,进阶版解不能用来解基础版,因为处理t耗时远超过遍历t.

**标签:**[数组],[贪心],[偏易]

```python
#进阶版解
def isSubsequence(self, s: str, t: str) -> bool:
    '''进阶的解法:
    '''
    m = len(t)
    hmap = {}
    hmap[-1]={}
    for idx,elem in enumerate(t):
        hmap[idx]={}
        for i in range(-1,idx):
            if elem not in hmap[i]:
                hmap[i][elem]=idx
    n = len(s)
    cur = -1
    for i in range(n):
        if s[i] in hmap[cur]:
            cur = hmap[cur][s[i]]
        else:
            return False
    return True

#基本版解
def isSubsequence(self, s: str, t: str) -> bool:
    '''进阶的解法很有趣,我也开始也没想到.
    '''
    a = list(s)
    a.reverse()
    if not a: return True
    for elem in t:
        if a[-1] == elem:
            a.pop()
            if not a: return True
    return False
```

##### 03_14

忙的一道题都没做

##### 03_13

**hot321** *89'23+{oo}+{5}* {oo}表示没通过所有样例
垃圾题!不配留名字,也不配被讨论.做了尼玛九十分钟还是看了答案还错了三次还有问题.真当自己多重要啊傻逼.

##### 03_09

hot402 *18'40+{0}* 去除前导0不在k之内 ,072 *21'37+{5}*,写起来容易但思路想不到 ,008 *22'03+{0}+{1}* 就是考虑情况要周全一些.

**008字符串转换整数 (atoi)**  *22'03+{1}+{2.5}*
请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。
函数 myAtoi(string s) 的算法如下：
    读入字符串并丢弃无用的前导空格
    检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
    读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
    将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
    如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为 −231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。
    返回整数作为最终结果。
注意：
    本题中的空白字符只包括空格字符 ' ' 。
    除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。

**解析:**1.看答案是不知道上界怎么处理,结果发现python不用管,cpp要用long定义. 2.错了一次是在最后循环外面返回的时候(全部解析合法),忘了把符号加上. 3.总体来说,是考设计,思考不难

**标签:**[字符串],[中等],[规则设计]

```python
def myAtoi(self, s: str) -> int:
    '''大数上限python会自动改变储存空间扩容,C++只能提前定义成long long
    '''
    NB,PB = 2**31,2**31-1
    ct,flag=0,0
    neg = False
    fuhao = {'+','-'}
    shuzi = {'0','1','2','3','4','5','6','7','8','9'}
    for elem in s:
        #前导的梳理
        if flag==0:
            if elem == ' ': continue
            elif elem not in fuhao and elem not in shuzi:
                return ct
            else:
                if elem =='+': pass
                elif elem == '-': neg=True
                else: ct=ct*10+int(elem)
                flag=1
        #数字位的梳理
        elif flag==1:
            if elem in shuzi:
                ct=ct*10+int(elem)
                if neg==False and ct>PB:
                    return PB
                if neg==True and ct>NB:
                    return -1*NB
            else:
                return ct if not neg else ct*-1 
    return ct if not neg else ct*-1 
```

**072编辑距离**  *21'37+{5}* 
给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
你可以对一个单词进行如下三种操作：
    插入一个字符
    删除一个字符
    替换一个字符

**解析:**关键在与能想通'插入一个字符','删除一个字符','替换一个字符'等价于:A末尾+1,B末尾+1,AB末尾同时+1的状态转移方程.考察的时候还会考各种变体就尼玛离谱.

**标签:**[困难],[动态规划],[字符串]

```python
def minDistance(self, word1: str, word2: str) -> int:
    '''这道题不仅要掌握题,还有很多变体??
    '''
    n1,n2 = len(word1),len(word2)
    dp = [[0 for x in range(n2+1)] for x in range(n1+1)]
    for i in range(n1+1):
        dp[i][0]=i
    for j in range(n2+1):
        dp[0][j]=j
    for i in range(1,n1+1):
        for j in range(1,n2+1):
            if word1[i-1]==word2[j-1]:
                a = dp[i-1][j-1]
            else:
                a = dp[i-1][j-1]+1
            b = dp[i-1][j]+1
            c = dp[i][j-1]+1
            dp[i][j]=min(a,b,c)
    return dp[n1][n2]
```

**hot402移掉 K 位数字**  *18'40+{0}*
给你一个以字符串表示的非负整数 num 和一个整数 k ，移除这个数中的 k 位数字，使得剩下的数字最小。请你以字符串形式返回这个最小的数字。

**解析:**本题是316的简化版.单调栈.值的注意的是,在去除高位后如果出现前导零,为保证格式正确会自动清除不算在k位数字之中.

**标签:**[单调栈],[中等]

```python
def removeKdigits(self, num: str, k: int) -> str:
    mon_stack = []
    n = len(num)
    for nb in num:
        while(mon_stack and int(nb)<int(mon_stack[-1]) and k>0):
            mon_stack.pop()
            k-=1
        if mon_stack or nb !='0' :
            mon_stack.append(nb)

    while(k>0 and mon_stack):
        k-=1
        mon_stack.pop()
    #后处理
    ans =  ''.join(mon_stack)
    if not ans: return "0"
    else: return ans
```

##### 03_08

hot316 *33'22+{0}+{5}*初见杀,明天做做类似的题 ,169 *22'16+{0}+{2.5}* 哈希很好想,但其他解法也挺多的 , hot543 *6'53+{0}+{0}*, c++:125,整理STL库和基本数据结构的内容.

**543二叉树的直径** *6'53+{0}+{0}*
给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。

**解析:**递归左右子树,其实不简单,但我做过太多类似类型的题目了,很熟悉.

**标签:**[二叉树],[递归],[容易]

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        def dfs(root):
            if not root:
                return 0
            left = dfs(root.left)
            right = dfs(root.right)
            dis = left+right
            global ans
            if dis>ans: ans = dis
            if left>right: return left+1
            else: return right+1
        global ans
        ans = 0
        dfs(root)
        return ans
```

```cpp
class Solution {
public:
    int ans; //声明一个公有变量,类中的所有函数都可以访问这个变量
    int depth(TreeNode* rt){
        if (rt==NULL) {
            return 0;
        }
        int L = depth(rt->left); //结构体指针地址的内容用->,结构体本身用.
        int R = depth(rt->right);
        ans = max(ans,L+R);
        return max(L,R)+1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 0;//初始化
        depth(root);
        return ans;
    }
};
```

**169多数元素** *22'16+{0}+{2.5}*
给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。

**解析:**oN遍历肯定很简单,但企业不可能让你这么简单.肯定会要求,空间复杂度O1的方法.答案五花八门.回溯啊排序啊什么的.但我觉得位运算真正实现了时间ON+空间O1.位上界,每隔符号最多做32次位操作,属于系数比较大的常数级别.如果数字大小有限制,系数会进一步减小.那个{2.5}是因为忘了取最低位数值和位移操作了.

**标签:**[数组],[位运算],[中等]

```python
def majorityElement(self, nums: List[int]) -> int:
    wei = [0]*32
    neg = 0
    for num in nums:
        if num<0: 
            neg+=1
            num *= -1
        ct=0
        while num>0:
            wei[ct]+=num&1 ##最低位数值
            num=num>>1 ##右移1位
            ct+=1
    ans = 0
    ct,bj = 0,len(nums)//2+1
    for w in wei:
        if w>=bj:
            ans+=2**ct
        ct+=1
    return ans
```

**316去除重复字符**  *33'22+{0}+{5}*
给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。

**解析:**初见杀,第一次见真不会.首先用单调栈保证字典序,然后用哈希表记录出现次数,还有贪心的想法,最开始保留下来的字母,后续相同字母都应该删除.我对于字典序问题还是有点怕.

**标签:**[偏难],[字符串],[单调栈],[字典序]

```python
def removeDuplicateLetters(self, s: str) -> str:
    '''这题如果没有402做铺垫是真不好想出来啊
    '''
    from collections import defaultdict
    hmap = defaultdict(int)
    stack = []
    vis = set()
    for elem in s:
        hmap[elem]+=1
    for elem in s:
        if elem in vis: 
            hmap[elem]-=1
            continue
        while(stack and ord(elem)<ord(stack[-1]) \
                and hmap[stack[-1]]>1):
                hmap[stack[-1]] -= 1
                vis.remove(stack[-1])
                stack.pop()
        stack.append(elem)
        vis.add(elem)
    return ''.join(stack)
```

##### 03_07

hot165 *(12'11+{0})* 要求用双指针版本, 070 *(2'54+{0})* 居然还有矩阵快速幂这种东西?我就不打算准备这个了, 232 *(7'57+{0})* 这道题绝对做过,咋没记录下来; C++实现一个简单题 062

**232用栈实现队列** *(7'57+{0})*
请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
实现 MyQueue 类：
    void push(int x) 将元素 x 推到队列的末尾
    int pop() 从队列的开头移除并返回元素
    int peek() 返回队列开头的元素
    boolean empty() 如果队列为空，返回 true ；否则，返回 false
说明：
    你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
    你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

**解析:**可以平均O(1)操作.比offerI09要复杂一些.但我做的更快更好.说明我已经完全掌握了.

**标签:**[辅助栈],[偏易]

```python
class MyQueue:

    def __init__(self):
        self.stacktail = []
        self.stackhead = []

    def push(self, x: int) -> None:
        self.stacktail.append(x)

    def pop(self) -> int:
        if not self.stackhead:
            self._switchstack()
        return self.stackhead.pop()

    def peek(self) -> int:
        if not self.stackhead:
            self._switchstack()
        return self.stackhead[-1]

    def empty(self) -> bool:
        if self.stackhead or self.stacktail:
            return False
        else:
            return True

    def _switchstack(self):
        while(self.stacktail):
            elem = self.stacktail.pop()
            self.stackhead.append(elem)
```

**070爬楼梯** *(2'54+{0})*
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

**解析:**一维线性动归,可以空间优化不建立显示数组O(1).但我没想到还有矩阵快速幂这种操作66.

**标签:**[容易],[动态规划]

```python
def climbStairs(self, n: int) -> int:
    if n==1: return 1
    if n==2: return 2
    n1,n2=1,2
    for i in range(3,n+1):
        nex = n1+n2
        n1=n2
        n2=nex
    return nex
```

**hot165比较版本号** *(12'11+{0})*
给你两个版本号 version1 和 version2 ，请你比较它们。
版本号由一个或多个修订号组成，各修订号由一个 '.' 连接。每个修订号由 多位数字 组成，可能包含 前导零 。每个版本号至少包含一个字符。修订号从左到右编号，下标从 0 开始，最左边的修订号下标为 0 ，下一个修订号下标为 1 ，以此类推。例如，2.5.33 和 0.1 都是有效的版本号。
比较版本号时，请按从左到右的顺序依次比较它们的修订号。比较修订号时，只需比较 忽略任何前导零后的整数值 。也就是说，修订号 1 和修订号 001 相等 。如果版本号没有指定某个下标处的修订号，则该修订号视为 0 。例如，版本 1.0 小于版本 1.1 ，因为它们下标为 0 的修订号相同，而下标为 1 的修订号分别为 0 和 1 ，0 < 1 。
返回规则如下：
    如果 version1 > version2 返回 1，
    如果 version1 < version2 返回 -1，
    除此之外返回 0。

**解析:** 和判断网络地址是否合法那道题一样,更多考阅读理解.CodeTop上评论说不能用split,那也无非是双指针/单指针的一个操作.

**标签:**[偏易],[字符串],[阅读理解]

```python
def compareVersion(self, version1: str, version2: str) -> int:
    ver1, ver2 = version1.split('.'), version2.split('.')
    n1,n2 = len(ver1),len(ver2)
    if n1<n2: ver1.extend([0]*(n2-n1))
    else: ver2.extend([0]*(n1-n2))
    ver1 = [int(x) for x in ver1]
    ver2 = [int(x) for x in ver2]
    for i in range(len(ver1)):
        if ver1[i]>ver2[i]:return 1
        elif ver2[i]>ver1[i]:return -1
    return 0
```

##### 03_06

hot 236 *20'39+{0}* ,047 *11'44+{0}* ,124 *11'50 + {1}*  看:094,142,300
堆排序,快速排序(33'+{1}),归并排序(25'+{0}) *03_15 排序题测试可以在hot912中测*

**hot124二叉树中的最大路径和** *11'50 + {1}*  *2.(04_04 cpp) 15'39+{0}+{0} *
路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
路径和 是路径中各节点值的总和。
给你一个二叉树的根节点 root ，返回其 最大路径和 。

**解析:**初见杀,第二次做就容易了很多.分别递归左子树和右子树.错的那一次是因为没有考虑负数情况.如果左右子树都是负数,只返回当前节点才是最大解.

**标签:**[二叉树],[递归],[中等]

```python
def maxPathSum(self, root: Optional[TreeNode]) -> int:
    global ans
    ans = float('-inf')
    def dfs(cur):
        if not cur: return 0
        left = dfs(cur.left)
        right = dfs(cur.right)
        global ans
        tans = cur.val+left if left>0 else cur.val
        tans = tans+right if right>0 else tans
        if tans > ans:
            ans = tans
        if left>0 or right>0:
            return cur.val+left if left>right else cur.val+right
        else:
            return cur.val
    dfs(root)
    return ans
```

```cpp
#define V vector<int>
#define VV vector<vector<int>>
class Solution {
public:
    int m_ct=0;
    V m_du;
    V m_visit;
    VV edge;
    void dfs(int cur){
        m_visit[cur]=1;m_ct+=1;
        for (int pt: edge[cur]){
            m_du[pt]-=1;
            if (m_du[pt]==0 and m_visit[pt]==0){
                dfs(pt);  }  }}
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n=numCourses,i,cur;
        m_du=V(n+1,0);m_visit=V(n+1,0);
        V m_null;
        edge = VV (n+1);
        VV& pre = prerequisites;
        for (const V & pt: pre){
            int ed=pt[0],st = pt[1];
            edge[st].push_back(ed);
            m_du[ed]+=1;
            }
        for (i=0;i<n;i++){
            cout<<m_du[i]<<" "<<m_visit[i]<<endl;
            if (m_du[i]==0 and m_visit[i]==0){
                dfs(i);}}
        if (m_ct==n){cout<<"true"<<endl;return true;}
        else{cout<<"false"<<endl;return false;}
    }};
```

**hot047全排列II** *11'44+{0}*
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列

**解析:**dfs+减枝

**标签:**[偏易],[减枝],[搜索]

```python
def permuteUnique(self, nums: List[int]) -> List[List[int]]:
    ans = []
    nums.sort()
    def dfs(cur,pool):
        if not pool: 
            ans.append(cur[:])
            return
        for idx, elem in enumerate(pool):
            if idx>0 and elem == pool[idx-1]: continue
            cur.append(elem)
            dfs(cur,pool[:idx]+pool[idx+1:])
            cur.pop()
    dfs([],nums)
    return ans
```

**1&03推排序**  *2.(03_15) 25'11+{0}*  *3.(04_11) 62'+{0}+{5} CPP*

**解析:**(04_11)在算法层面也犯了错误:为了递归的满足根节点大于左右子树这个定义,建堆的时候如果要调整,需要递归的调整而不是一次调整.
先建构一个大根堆,然后每次把头和尾交换,对头进行调整,长度-1.关键要记住,对于层序数组表达的二叉树,长度为n则首非叶节点为n//2-1,对节点索引i如果左右子树存在的话,左子树为i\*2+1,右子树为i\*2+2. *03_15:*大根堆建法是从第一个非叶子节点(n//2-1)开始调整. 堆排序是三大排序算法里向对简单的了.

```python
#03_15版本
def sortArray(self, nums: List[int]) -> List[int]:
    n = len(nums)
    k = n//2-1
    for i in range(k,-1,-1):
        self.adjust(nums,i,n-1)
    for i in range(n-1,-1,-1):
        nums[0],nums[i]=nums[i],nums[0]
        self.adjust(nums,0,i-1)
    return nums
  
def adjust(self,nums,cur,tail):
    while( 2*cur+1 <= tail ):
        lp,rp = 2*cur+1,2*cur+2
        l = nums[lp]
        r = nums[rp] if rp<=tail else float('-inf')
        if l<=r and r>nums[cur]:
            nums[cur],nums[rp] = nums[rp],nums[cur]
            cur = rp
        elif l>r and l>nums[cur]:
            nums[cur],nums[lp] = nums[lp],nums[cur]
            cur = lp
        else:
            return

def sortArray(self, nums: List[int]) -> List[int]:
    '''堆排序:
    '''
    arr = nums
    n = len(arr)
    nleaf = n//2-1
  
    def adjust(arr,st,ed):
        while(True):
            cur = arr[st]
            left,right = st*2+1,st*2+2
            nleft = arr[left] if left<=ed else cur-1
            nright = arr[right] if right<=ed else cur-1
            if cur >= nleft and cur>=nright: return
            else:
                if nleft>=nright:
                    arr[st],arr[left] = arr[left],arr[st]
                    st=left
                else:
                    arr[st],arr[right] = arr[right],arr[st]
                    st=right
  
    for i in range(nleaf,-1,-1):
        adjust(arr,i,n-1)
    for i in range(n-1,-1,-1):
        arr[0],arr[i]=arr[i],arr[0]
        adjust(arr,0,i-1)
    return arr
```

```cpp
class Solution {
public:
    vector<int> * arr;
    int i,j,k,n;
    int lft,rt;
    void adjust(int I,int N){
        // cout<<I<<" "<<N<<" "<<endl;
        lft = 2*I;rt = 2*I+1;
        int lft_N= (lft<=N)?(*arr)[lft]:int(-1e5);
        int rt_N= (rt<=N)?(*arr)[rt]:int(-1e5);
        if (lft<=N and lft_N>rt_N and lft_N>(*arr)[I]){
            swap((*arr)[lft],(*arr)[I]);
            adjust(lft,N);}
        if (rt<=N and rt_N>=lft_N and rt_N>(*arr)[I]){
            swap((*arr)[rt],(*arr)[I]);
            adjust(rt,N);}
    }

    vector<int> sortArray(vector<int>& nums) {
        n = nums.size();
        arr = &nums;
        nums.insert(nums.begin(),0);
        for(i=n/2;i>=1;i--) adjust(i,n);
        for (i=n;i>=1;i--) {
            swap((*arr)[1],(*arr)[i]);
            adjust(1,i-1);
        }
        nums.erase(nums.begin());
        return nums;
    }
};
```

##### 03_05

**10003pythonIO练习**

```python
#sort默认就是用字典序排的
#input().strip()
#try: ... except: ...
```

##### 03_04

做:hot415(19'21+{0}), 042 (58'09+{0}+{2.5}), 143 (29'16+{0}+{0})

**hot143重排链表** (29'16+{0}+{2.5}) *2.(03_20) 25'01+{0}+2.5*
给定一个单链表 L 的头节点 head ，单链表 L 表示为：
L0 → L1 → … → Ln - 1 → Ln
请将其重新排列后变为：
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

**解析:** (03_20)还是一开始以为是线性表的题,没考虑到有O1的解,但做完这次感觉已经算很有印象了.
首先实现的是线性表递归解,空间是on,但是会比递推要占空间大(n前面的系数大一些,但这不能成为我不用递归的理由.).错误1:递归最后一层应该让结尾节点指向空,不然验证不了会报超时(很合理,成环了之后循环读取).错误2:对链表先找中点,再翻转,再一次连接可以实现O(1)空间复杂度+O(N)时间复杂度.(我之前一直以为不线性表会让时间变成N2)

**标签:**[重排链表],[中等]

```python
def reorderList(self, head: Optional[ListNode]) -> None:
    """
    Do not return anything, modify head in-place instead.
    """
    def conn(st,ed):
        if ed-st==0 or ed-st==1: 
            nlist[ed].next=None
            return
        else:
            conn(st+1,ed-1)
            nlist[st].next = nlist[ed]
            nlist[ed].next = nlist[st+1]
            return


    nlist = []
    cur = head
    while(cur):
        nlist.append(cur)
        cur = cur.next
    n = len(nlist)
    conn(0,n-1)
```

**hot042接雨水** *1.(58'09+{0}+{2.5})*  *2.(03_20) 26'14+{0}*(空间又没有优化) 
*3.(04_06)26'+{1} CPP*(空间优化)
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

**解析:**(03_20)写的没啥困难了,单调栈.但一开始看到先找到最大值,没理解为啥要找最大值.多浪费了时间.后来读了解析才发现空间可以优化到O1.
这道题确实属于企业爱考的类型,代码不复杂,但是思考量很大.面试如果有思路(做过)可能十几分钟就做出来了,没思路可能一个小时都够呛.我想了一个小时,写出来一个单调栈.但是空间是ON的.有一种思考量和空间和代码都更简洁的写法是,找最大的柱子,但后作为左边的右墙和右边的左墙来求解.下次要把这种做法也给写出来.

**标签:**[贪心],[偏难],[掌握]

```python
#单调栈写法
def trap(self, height: List[int]) -> int:
    m_stack = [(-1,-1)]
    cur_sum = 0
    for c_idx,c_high in enumerate(height):
        if len(m_stack)==1 or m_stack[-1][0]>c_high:
            m_stack.append((c_high,c_idx))
        else:
            while(len(m_stack)>1):
                t_high = m_stack.pop()[0]
                if len(m_stack)==1:
                    break
                hh = min(m_stack[-1][0],c_high)-t_high
                ww = c_idx-m_stack[-1][1]-1
                cur_sum+= ww*hh
                if c_high<m_stack[-1][0]:
                    break
            m_stack.append([c_high,c_idx])
    return cur_sum
```
```cpp
class Solution {
public:
    int i,j,k,lft,rt,ans,m_ht,m_idx;
    int FindMaxIdx(vector<int>& ht){
        auto maxm=-1;
        int idx=-1;
        for (i=0;i<ht.size();i++){
            if(ht[i]>maxm){
                maxm=ht[i];
                idx = i;
            }
        }return idx;
    }
    int trap(vector<int>& height) {
        auto&arr=height;
        ans=0;
        m_idx = FindMaxIdx(arr);
        m_ht=arr[m_idx];lft=-1,rt=-1;
        for(i=0;i<m_idx;i++){
            if (lft<arr[i]) lft=arr[i];
            else ans+=(lft-arr[i]);
        }

        for(i=arr.size()-1;i>m_idx;i--){
            if (rt<arr[i]) rt=arr[i];
            else ans+=(rt-arr[i]);
        }
        return ans;
    }
};
```

**hot415字符串相加** *(19'21+{0})*
给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和并同样以字符串形式返回。
你不能使用任何內建的用于处理大整数的库（比如 BigInteger）， 也不能直接将输入的字符串转换为整数形式。

**解析:**大数加法.可以先转化成列表然后处理,也可以直接以字符串的形式处理.字符串形式处理因为不用转化,效率更高.可以翻转或者不翻转,不翻转思考量更复杂一点,翻转要多操作一下.但也是ON的复杂度.

**标签:**[字符串],[偏易],[数组]

```python
def addStrings(self, num1: str, num2: str) -> str:
    num1,num2 = list(num1),list(num2)
    if len(num1)< len(num2): num1,num2 = num2,num1
    n1,n2=len(num1),len(num2)
    num1.reverse()
    num2.reverse()
    # ans = []
    jw = 0
    for pos in range(n1):
        if pos < n2:
            cur = int(num1[pos])+int(num2[pos])+jw
        else:
            cur = int(num1[pos])+jw
        jw = cur//10
        benwei=cur-jw*10
        num1[pos]=benwei
    if jw ==1:
        num1.append(1)
    num1.reverse()
    num1 = ''.join(str(x) for x in num1)
    return num1
```

##### 03_03

做:054 *51'16+{0}* ,023 *13'51+{1}* 错的有点冤,没搞清输入输出而已, 092 *25'21+{9}* (这应该比按对翻转025简单,怎么感觉更复杂了反而,确实比025简单一点,耗时也少一些)  看:160

**hot023合并k个升序链表** *13'51+{1}*  *2.(04_10) {30'27}+{0} CPP*
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。

**解析:**(04_10)先用优先队列储存每个链表头,每次返回堆头最小元,然后再入堆最小元对应链表的下一位.可以达到(n*k)logk复杂度.之前用python实现的相当于归并排序的后半段,时间复杂度一样,但空间会略优一些.但这次主要是为了学习CPP的优先队列.
错是输入输出每搞清楚,空链表以为return[]结果应该是return None.链表版的归并排序,的合并部分.

**标签:**[链表],[中等]

```python
def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
    if not lists: return None
    def merge(lists):
        n = len(lists)
        if n==1: return lists[0]
        elif n==2:
            a,b = lists
            head = ListNode(-1)
            cur = head
            while(a and b):
                if a.val > b.val:
                    cur.next = b
                    b = b.next
                else:
                    cur.next = a
                    a = a.next
                cur = cur.next
            cur.next = a if a else b
            return head.next
        else:
            mid = n//2
            a = merge(lists[:mid])
            b = merge(lists[mid:])
            return merge([a,b])
    return merge(lists)
```
```cpp
class Solution {
public:
    struct compare{
        bool operator()(LN* a, LN* b){
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*,vector<ListNode*>,compare > q;
        for (auto ln: lists){if(ln)q.push(ln);}
        LN Phead;
        LN* cur = &Phead;
        while(not q.empty()){
            LN* tmp = q.top();q.pop();
            cur->next = tmp;
            if (tmp->next) q.push(tmp->next);
            cur = cur->next;
        }
        return Phead.next;
    }
};
```



**hot092反转链表 II** *(03_03) 25'21+{9}*
给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。

**解析:**0-25的简化版,0-25需要把每一段前后连起来,这个只需要反转中间一段即可.

**标签:**[链表],[翻转],[中等]

```python
def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
  
    def reverse(st,num,prev):
        ct=0
        cur = st
        while(ct<num):
            ct+=1
            nex = cur.next
            cur.next = prev
            prev = cur
            cur = nex
        return prev, st, cur
  
    ct=1
    st = head
    prev = None
    num = right-left+1
    while(True):
        if ct<left:
            prev = st
            st = st.next
            ct+=1
        else:
            c_head = prev
            t_head,t_tail,c_tail = reverse(st,num,prev)
            if c_head: c_head.next = t_head
            else: head = t_head #头节点
            t_tail.next = c_tail
            return head
```

**hot054螺旋矩阵** *51'16+{0}* *(03_24)*  *(06_19){40'56}+{0}+{0}*
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

**解析:**(03_24)由于一开始每次拐弯只约束了一个条件,导致总是有溢出的情况.在时间复杂度没有指数增长的前提下,请不要吝啬增加额外的约束; 如果每次移动指定个格子,则可以不用判断四个边界,但似需要确定走的路长度.都差不多;
(03_02)虽然做出来了,但是代码可以简单很多.不需要一个一个判断.一个循环有四个环节.这个题的好处是,就算在其中一个环节结束了,后续环节移动0仍然不会产生阻碍.

**标签:**[数组],[模拟],[中等],[掌握]

```cpp
class Solution {
public:
    vector<int>ans;int ms,ns,me,ne;
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        me=matrix.size()-1; if(me==-1)return ans;
        ne=matrix[0].size()-1; if(ne==-1) return ans;
        ms=0,ns=0;
        int i=-1,j=-1,i_r=0,j_r=0;
        while(i_r!=i or j_r!=j){
            i=i_r;j=j_r;
            circle(i,j,matrix,i_r,j_r);
        }return ans;
    }

    void circle(int i,int j, vector<vector<int>>& matrix,int & i_r,int & j_r){
        while(i>=ms and i<=me and j>=ns and j<=ne)
        {ans.emplace_back(matrix[i][j]); j++; }j--;i++;ms++;
        while(i>=ms and i<=me and j>=ns and j<=ne)
        {ans.emplace_back(matrix[i][j]); i++; }i--;j--;ne--;
        while(i>=ms and i<=me and j>=ns and j<=ne)
        {ans.emplace_back(matrix[i][j]); j--; }j++;i--;me--;
        while(i>=ms and i<=me and j>=ns and j<=ne)
        {ans.emplace_back(matrix[i][j]); i--; }i++;j++;ns++;
        i_r=i;j_r=j;    }
};
```


##### 03_02

做:200 *43'50+{1}+{5}*, 088 *39'50+{0}+{5}*(又是一道初见杀,写的超复杂的一个解,结果逆向双指针就能结局了), 103 *14'25+{0}+{0}* 看:121,005

**hot103二叉树的锯齿形层序遍历** *14'25+{0}+{0}* *(07_14){19'}*
给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

**解析:**之前一定做过类似的,应该是在offerI里面层序遍历的变种

**标签:**[二叉树],[层序遍历],[遍历],[中等],[掌握]
```cpp
 #define eb emplace_back
 #define pb pop_back
 #define vit vector<TreeNode*>
 #define TN TreeNode
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vit stack,tmp;
        vector<int> cans;
        vector<vector<int>>ans;
        TN * cur;
        if(root==NULL){return ans;}
        else { stack.eb(root); }
        while(stack.size()){
            //先左后右压栈
            while(stack.size()){
                cur=stack.back(); cans.eb(cur->val);
                stack.pb();
                if(cur->left) { tmp.eb(cur->left);}
                if(cur->right) { tmp.eb(cur->right);}
            }if(cans.size()) { ans.eb(cans); cans.clear();}
            stack=tmp; tmp.clear();
            while(stack.size()){
                //先右后左压栈
                cur=stack.back(); cans.eb(cur->val);
                stack.pb();
                if(cur->right){ tmp.eb(cur->right);}
                if(cur->left) { tmp.eb(cur->left);}
            }if(cans.size()) { ans.eb(cans); cans.clear();}
            stack=tmp; tmp.clear();
        }
        return ans;
    }
};
```

```python
def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
    if not root: return []
    stack_cur = [root]
    stack_nex = []
    ans = []
    tmp = []
    sig = 'left'
    while(True):
        if not stack_cur and not stack_nex: 
            ans.append(tmp)
            return ans
        if not stack_cur:
            ans.append(tmp)
            tmp = []
            stack_cur = stack_nex
            stack_nex = []
            sig = 'right' if sig=='left' else 'left'
        while(stack_cur):
            cur = stack_cur.pop()
            tmp.append(cur.val)
            if sig == 'left':
                if cur.left: stack_nex.append(cur.left)
                if cur.right: stack_nex.append(cur.right)
            else:
                if cur.right: stack_nex.append(cur.right)
                if cur.left: stack_nex.append(cur.left)
```

**hot088合并两个有序数组** *1.(03_02) 39'50+{0}+{5}* *2.(03_23) 24'22+{0}*
给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。
注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。

**解析:**(03_23)第二次仍然没有想到时O(M+N),空O(1)后端指针.从后往前遍历.
初见杀,不知道题目要我到底干啥.我以为一定不能使用额外空间.然后用了时间复杂度N2的搬运.但其实存在on的方式,后端指针.要重做一遍.

**标签:**[数组],[偏易],[指针]

```python
def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
    """
    Do not return anything, modify nums1 in-place instead.
    """
    def move():
        for i in range(end1,left1-1,-1):
            nums1[i+dis] = nums1[i]
    def copy():
        for i in range(left2,left2+dis,1):
            pos1 = i-left2+left1
            nums1[pos1]=nums2[i]


    left1,left2=0,0
    right2=left2
    end1 = m-1
    while(end1<n+m-1):
        while(right2<n and nums1[left1]>nums2[right2]):
            right2+=1
        if right2>left2:
            dis = right2-left2
            move()
            copy()
            end1+=dis
            left1+=dis
            left2=right2
        if left1>end1:
            right2=n
            dis = right2-left2
            copy()
            end1+=dis
        left1+=1
```

**hot200岛屿数量** *1.(03_02) 43'50+{1}+{5}* *2.(03_23) 16'24+{1}* *3(07_14)*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。

**解析:**(03_23) 很简单记忆化bfs,错了一次是因为没考虑边界.
一开始写错了,在dfs搜索的时候,坐标用的和循环坐标一样.如果是一重循环这样没问题,但二重循环j循环没结束是不会刷新i的,i被覆盖之后就是被覆盖的值了.所以错了.同时方法也有问题,不需要用set记忆化的,只需要把访问过的地方设置成1就行了,节省空间.

**标签:**[搜索],[广度优先搜索],[中等],[掌握]

```python
def numIslands(self, grid: List[List[str]]) -> int:
    from collections import deque
    m,n = len(grid),len(grid[0])
    que = deque([])
    ct = 0
    for i in range(m):
        for j in range(n):
            if grid[i][j]=='0': continue
            else:
                ct+=1
                # print(i,j)
                que.append((i,j))
                while(que):
                    #注意不能变量名和循环指针混用,
                    #这样循环j的时候i会发生变化无法及时纠正
                    si,sj = que.popleft()
                    self.check([si+1,sj],grid,que,m,n)
                    self.check([si-1,sj],grid,que,m,n)
                    self.check([si,sj+1],grid,que,m,n)
                    self.check([si,sj-1],grid,que,m,n)
    return ct
def check(self,pos,grid,que,m,n):
    i,j = pos
    if i<0 or i>=m or j<0 or j>=n: return
    if grid[i][j]=='1':
        grid[i][j]='0'
        que.append((i,j))
```

##### 03_01

160 (12'+{0}) , offerI09 (17'+{0}+{5}), 468 (28'07+{1}) , 1438 (30'+{0})(也是有点初见杀) 复习(300,022,141)

**hot1438绝对差不超过限制的最长连续子数组**   *(30'+{0})* *2.(04_05) 67'+{0} cpp*

**解析:**(04_05)C++有两个坑:1.不需要记录idx其实,这样可以快一倍. 2.如果要使用二维数组,要么一开始定义好二维的int矩阵,要么vector\<vector\<int\>\>; 如果用vector<int*>这样,看起来很聪明,但实际上指针不好操作.容易出现内存错误.
也是初见杀.如果没做过类似的想不到要用两个辅助队列来动态监督头尾节点,可以实现o(n)复杂度的查找.参考答案中还有使用有序数组或者AVL的想法,复杂度还是nlogn,而且有序数组或者AVL面试时候是调用现成的包,没有我最开始的做法的能体现思考量.

**标签:**[数组],[偏难]

```python
def longestSubarray(self, nums: List[int], limit: int) -> int:
    from collections import deque
    left,right = 0,0
    n = len(nums)
    ans = 1
    max_que,min_que = deque([[nums[0],0]]),deque([[nums[0],0]])
    while(right<n-1):
        right+=1
        cur = [nums[right],right]
        while(max_que and max_que[-1][0]<=cur[0]):
            max_que.pop()
        max_que.append(cur)
        while(min_que and min_que[-1][0]>=cur[0]):
            min_que.pop()
        min_que.append(cur)

        while(max_que[0][0]-min_que[0][0]>limit):
            left+=1
            while (left>max_que[0][1]):max_que.popleft()
            while (left>min_que[0][1]):min_que.popleft()

        if right-left+1>ans: ans=right-left+1
    return ans
```

**hot468验证IP地址**  (28'07+{1})

**解析:**没有算法难度,但是有要把情况考虑全面.错的那一次是忽略了十六进制数在字母上只能是a-f,写成了a-z

**标签:**[字符串],[中等],[规则设计],[烂题]

```python
def validIPAddress(self, queryIP: str) -> str:
    s = queryIP
    if '.' in s: #ipv4
        s = s.split('.')
        if len(s)!=4: return "Neither"
        for word in s:
            ret = self.check4(word)
            if not ret: return "Neither"
        return "IPv4"
    if ':' in s:
        s = s.split(':')
        if len(s) != 8: return "Neither"
        for word in s:
            ret = self.check6(word)
            if not ret: return "Neither"
        return "IPv6"
    return "Neither"
def check4(self,word):
    if len(word)<1 or len(word)>3: return False
    num = 0
    for l in word:
        #非法字符
        if ord(l)<ord('0') or ord(l)>ord('9'): return False
        #前导零
        l = int(l)
        if l==0 and num==0 and len(word)>1: return False
        num=num*10+l
    if num>255: return False
    return True

def check6(self,word):
    if len(word)<1 or len(word)>4: return False
    for l in word:
        if ( ord(l)<ord('0') or ord(l)>ord('9') ) and \
        ( ord(l)<ord('a') or ord(l)>ord('f') ) and \
        ( ord(l)<ord('A') or ord(l)>ord('F') ): return False
    return True
```

**offerI09(hot232))** *(17'+{0}+{**5**})*

**解析:**hot232的简单版.辅助栈,有点初见杀的题.最开始的想法是每次要查找头节点都出栈到辅助栈,删除头节点在插回去.如果进行n次操作,复杂度接近O(n2).标答给出了一个元素只需要入栈出栈两次O(n)就可以实现的思路.要删头节点时如果辅助栈为空则把全部栈元素入栈出栈调入辅助栈中,这样辅助栈是顺序的.如果不为空则pop栈顶元素.这样避免了大量的无效增删操作.

**标签:**[辅助栈],[容易],[设计]

```python
class CQueue:
    def __init__(self):
        self.stack = []
        self.help = []
    def appendTail(self, value: int) -> None:
        self.stack.append(value)
    def deleteHead(self) -> int:
        if self.help: return self.help.pop()
        if not self.stack: return -1
        while(self.stack):
            self.help.append(self.stack.pop())
        ret = self.help.pop()
        return ret
# Your CQueue object will be instantiated and called as such:
# obj = CQueue()
# obj.appendTail(value)
# param_2 = obj.deleteHead()
```

**hot160相交链表**  *(12'+0)*
 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null .
图示两个链表在节点 c1 开始相交：

<img src="/home/qxy/Desktop/jupyter/leetcode/note.assets/160_statement.png" alt="160_statement" style="zoom: 80%;" />

题目数据 **保证** 整个链式结构中不存在环。
**注意**，函数返回结果后，链表必须 **保持其原始结构** 。

**解析:**初见杀,第二次做没难度,双指针,走到尽头交换走,如果能相遇则相遇点是起始节点,否则没有起始节点.

**标签:**[链表],[双指针],[偏易]

```python
def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> Optional[ListNode]:
    walk1,walk2 = headA,headB
    flag1,flag2 = True,True
    while(True):
        if walk1 == walk2: return walk1
        walk1 = walk1.next
        if not walk1:
            if flag1: 
                walk1 = headB
                flag1 = False
            else: return None
        walk2 = walk2.next
        if not walk2:
            if flag2: 
                walk2 = headA
                flag2 = False
            else: return None
```

##### 02_28

025 *(55'+{0}+ {0})*, ~~015~~ ,~~001~~ *15'+{0}*(这两道题整理在0218)
021 *(7'15+{0})*, 033 *(30'23+{0})*, 020 *(8'+{0})* ,019 (12'38+{0}), 155 *(17'45+{0})*

**hot155最小栈** *(17'45+{0})*
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
实现 MinStack 类:
    MinStack() 初始化堆栈对象。
    void push(int val) 将元素val推入堆栈。
    void pop() 删除堆栈顶部的元素。
    int top() 获取堆栈顶部的元素。
    int getMin() 获取堆栈中的最小元素。

**解析:** 初见杀,用一个栈储存最小值

**标签:** [栈],[较易]

```python
class MinStack:
    def __init__(self):
        self.stack = []
        self.minstk = []

    def push(self, val: int) -> None:
        self.stack.append(val)
        if not self.minstk: self.minstk.append(val)
        elif val<=self.minstk[-1]: self.minstk.append(val)

    def pop(self) -> None:
        val = self.stack.pop()
        if val == self.minstk[-1]:
            self.minstk.pop()

    def top(self) -> int:
        return self.stack[-1]

    def getMin(self) -> int:
        return self.minstk[-1]
```

**hot019删除链表的倒数第 N 个结点** *(12'38+{0})*
给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

**解析:**两种解法,第一种遍历两遍,第二种遍历一遍用列表存储然后进行删除.一种省空间一种省时间

**标签:**[链表],[偏易]

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
#一次遍历的方法
def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
    if not head.next: return None
    linklist = []
    tmp = head
    while(tmp):
        linklist.append(tmp)
        tmp = tmp.next
    tolen = len(linklist)
    k = tolen-n+1
    if k == 1: 
        linklist[0].next = None
        return linklist[1]
    if k == tolen:
        linklist[-2].next=None
        return linklist[0]
    else:
        k-=1
        linklist[k-1].next = linklist[k+1]
        linklist[k].next=None
        return linklist[0]
#两次遍历的方法
class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        length = cal_len(head)
        del_num = length-n+1
        head = del_head(head,del_num)
        return head

def cal_len(head):
    length=1
    while head.next !=None:
        length+=1
        head = head.next
    return length

def del_head(head,num):
    bj=head
    ct=1
    if num != 1:
        while ct!=num-1:
            ct+=1
            bj=bj.next
        bj.next = bj.next.next
    else:
        head = head.next
    return head
```

**hot020有效的括号** *(8'+{0})*
给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s` ，判断字符串是否有效。
有效字符串需满足：
1.左括号必须用相同类型的右括号闭合。
2.左括号必须以正确的顺序闭合。
3.每个右括号都有一个对应的相同类型的左括号。

**解析:**最基本的栈的使用

**标签:**[栈],[容易]

```python
def isValid(self, s: str) -> bool:
    stack = []
    hmap = {')':'(', '}':'{' , ']':'[' }
    for elem in s:
        if elem not in hmap:
            stack.append(elem)
        else :
            peidui = hmap[elem]
            if not stack or stack[-1]!=peidui:
                return False
            else:
                stack.pop()
    if not stack: return True
    else: return False
```

**hot021合并两个有序链表** *(7'15+{0})*
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

**解析:**合并链表里面最基本的题目

**标签:**[链表],[合并链表],[容易]

```python
def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
    dhead = ListNode(-1)
    cur = dhead
    while(list1 and list2):
        if list1.val<list2.val:
            cur.next = list1
            list1 = list1.next
        else:
            cur.next = list2
            list2 = list2.next
        cur = cur.next

    cur.next = list1 if list1 else list2
    return dhead.next
```

**hot025 K个一组翻转链表** *(55'+{0}+ {0})*
给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

**解析:**翻转之后的尾要对上翻转之后的头,同时判断是否是最后一段(最后一段不翻转).想错了两次导致多花时间.第一次以为翻完就可以了,第二次以为要递归,后面状态确定了才能确定前面状态.其实都不用.

**标签:**[链表],[偏难]

```python
def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
    reth = None
    nexhead = head
    reth,prevtail,end,nexhead = self.reverse(head,k)
    if end : return reth
    while(True):
        tmphead,tmptail,end,nexhead = self.reverse(nexhead,k)
        prevtail.next = tmphead
        prevtail = tmptail
        if end: return reth



def reverse(self,head,k):
    '''返回值:
    当前首节点,尾节点,是否有下一个链表,下一个链表首节点
    '''
    right= head
    ct = 1
    while(right.next and ct<k):
        right = right.next
        ct+=1
        if ct==k: break

    if ct<k: return head,right,True,None
    left = head
    prev = None
    right= right.next
    while(left != right):
        nex = left.next
        left.next = prev
        prev = left
        left = nex
    if not left: return prev,head,True,left
    else: return prev,head,False,left
```

##### 02_27

053(之前做过), ~~025~~

##### 02_26

找到了一个很好的网站,把力扣题目用面试出现频次进行了排列.要把这个网站里前 **2·00** 的题都二刷一遍,遇到不熟的知识点再触类旁通一波.
hot 206 *(07'07+{0})* ,146(49'40+{0}+{5}), 215(46'55+{0}+{5}),~~025~~

**hot215数组中的第K个最大元素** *215(46'55+{0}+{5})*
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

**解析:**看答案是认为快排并不能保证O(n),结果答案给的解释是,快排在寻找第k大元素的时候,渐进期望是o(n)...有点离谱

**标签:**[排序],[数组],[偏难]

```python
def findKthLargest(self, nums: List[int], k: int) -> int:
    def quicksort(l,r,i):
        tar = nums[i]
        nums[l],nums[i]=nums[i],nums[l]
        while(l<r):
            while(nums[r]>=tar and l<r):
                r-=1
            nums[r],nums[l]=nums[l],nums[r]
            while(nums[l]<=tar and l<r):
                l+=1
            nums[r],nums[l]=nums[l],nums[r]
        return l 
  
    left,right = 0,len(nums)-1
    k = len(nums)-k
    while(left<right):
        i = random.randint(left,right)
        # i=left
        pos = quicksort(left,right,i)
        if pos==k: return nums[pos]
        elif pos>k: right=pos-1
        else: left=pos+1
    return nums[left]
```

**hot146LRU缓存** *(49'40+{0}+{5})*
请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
    LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
    int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
    void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

**解析:**构造双链表,配合字典一起实现LRU.看答案是不相信复杂到要构造双链表,自己写双链表的插入和删除.没想到就是要求这个.思考量不大但是技术细节繁琐.

**标签:**[链表],[双链表],[偏难]

```python
class dnode():
    def __init__(self,keys,value):
        self.val = value
        self.key = keys
        self.prev = None
        self.next = None

class LRUCache:

    def __init__(self, capacity: int):
        self.hmap = {}
        self.head,self.tail = dnode(-1,-1),dnode(-1,-1)
        self.head.next = self.tail
        self.tail.prev = self.head
        self.length = 0
        self.mlen = capacity

    def get(self, key: int) -> int:
        if key in self.hmap:
            tmp = self.hmap[key]
            self.delete(tmp)
            self.insert_head(tmp)
            return self.hmap[key].val 
        else:
            return -1

    def put(self, key: int, value: int) -> None:
        if key in self.hmap:
            tmpnode = self.hmap[key]
            tmpnode.val = value
            self.delete(tmpnode)
            self.insert_head(tmpnode)
            return
        tmp = dnode(key,value)
        self.hmap[key]=tmp
        self.insert_head(tmp)
        self.length+=1
        if self.length > self.mlen:
            #删除最后一个元素
            last = self.tail.prev
            self.hmap.pop(last.key)
            self.delete(last)
            self.length-=1

    def insert_head(self,tmp):
        self.head.next.prev = tmp
        tmp.next = self.head.next
        self.head.next = tmp
        tmp.prev = self.head

    def delete(self,tmp):
        tmp.prev.next = tmp.next
        tmp.next.prev = tmp.prev

```

**hot206翻转链表**

**解析:**链表最基本的题

**标签:**[链表],[容易]

```python
def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
    prev = None
    cur = head
    while(cur):
        nex = cur.next
        cur.next = prev
        prev = cur
        cur = nex
    return prev
```

##### 02_25

整理之前做过的题和八股.比照常考面经资源整理自己做过的常考的知识点.

##### 02_24

offerII 08(209) *(27'18+{0})* ,09(713) *30'55+{1}+{5}* ,10(506) *33'+{0}+{5}*, 11 (33'+{1}+{5})

**offerII0II11(hot525)0和1个数相同的子数组**  *1.(02_24) 33'+{1}+{5}* *2.(03_24) 37'28+{0}+{5}*
给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度。

**解析:**(03_24)思路:由数据规模想到只能用ON的时间搞定.关键时要想到一段之间连续,等价于起点之前的01差值和起点之后的01差值是相同的.这样就说明了i-0.5的意义所在了.也能够想到前缀和这个特性了.关键还是在于分析数据结构.
第10题的困难版,即使是挨着做的我也没做出来你说说.

**标签:**[前缀和],[哈希],[困难]

```python
#(03_23)优化版,节省了声明pre列表的空间,并且一遍遍历解决问题
def findMaxLength(self, nums: List[int]) -> int:
    pre = 0
    n = len(nums)
    max_l = 0
    hmap = {0:-1}
    for i in range(n):
        pre += int( (nums[i]-0.5)*2 )
        if pre not in hmap:
            hmap[pre]=i
        else:
            try_l = i-hmap[pre]
            if try_l>max_l: max_l=try_l
    return max_l

def findMaxLength(self, nums: List[int]) -> int:
    pre = [int( (nums[0]-0.5)*2 )]
    for num in nums[1:]:
        pre.append( pre[-1]+int((num-0.5)*2) )
    # from collections import defaultdict
    hmap = {0:-1}
    ans = 0
    for idx,num in enumerate(pre):
        if num in hmap:
            if idx-hmap[num]>ans: ans=idx-hmap[num]
        else: hmap[num]=idx
    return ans
```

**0II10(hot560)和为 k 的子数组** *33'+{0}+{5}*
给定一个整数数组和一个整数 k ，请找到该数组中和为 k 的连续子数组的个数。

**解析:**前缀和+哈希,数组初见杀

**标签:**[前缀和],[哈希],[偏难]

```python
def subarraySum(self, nums: List[int], k: int) -> int: 
    from collections import defaultdict
    n = len(nums)
    hmap = defaultdict(int)
    hmap[0]=1
    ans = 0
    pre = [nums[0]]
    for i in range(1,len(nums)):
        pre.append(nums[i]+pre[-1])
  
    for i in range(n):
        ans+=hmap[pre[i]-k]
        hmap[pre[i]]+=1
    return ans
```

**0II09(hot713)乘积小于 K 的子数组** *30'55+{1}+{5}*
给定一个正整数数组 nums和整数 k ，请找出该数组内乘积小于 k 的连续的子数组的个数。

**解析:**right指针表示截至到右端指针的连续子数组.right和right+1之间的关系是,如果right中都大的话,right+1必大,所以下一层left可以从上一层的停住的地方开始判断而不遗漏.和数组结合起来的滑窗和前缀和要比字符串版本的困难.

**标签:**[数组],[滑动窗口],[偏难]

```python
def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
    if k==0: return 0
    n = len(nums)
    left,right=0,0
    sums=1
    ans = 0
    while(right<n):
        sums*=nums[right]
        while(sums>=k):
            if left<right:
                sums/=nums[left]
                left+=1
            else: break
        if sums<k: ans+=right-left+1
        right+=1
    return ans
```

**0II08(209): 和大于等于 target 的最短子数组** *(27'18+{0})*
给定一个含有 n 个正整数的数组和一个正整数 target 。
找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

**解析:**我以为这是比较难的滑窗题,没想到和剩下三个比这是最简单的.起码自己做出来了.

**标签:**[数组],[滑动窗口],[中等]

```python
def minSubArrayLen(self, target: int, nums: List[int]) -> int:
    n = len(nums)
    total=nums[0]
    left,right = 0,0
    ans = float('inf')
    if total>=target: return 1
    while(right<n-1):
        right+=1
        total+=nums[right]
        while(total>=target):
            if right-left+1<ans:
                ans = right-left+1
            total-=nums[left]
            left+=1
    if ans == float('inf'): return 0
    else: return ans
```

##### 02_23

学习归并排序,hot003 *(10'58+{0})* ,011 *(11'28+{0})*,031 *(15'35+{0)*,017 *(11'48+{0})*

**hot017电话号码的字母组合** *(11'48+{0})*
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

**解析:** 树,BFS题做多了之后感觉像是层序遍历的题.

**标签:** [数组],[遍历],[容易]

```python
def letterCombinations(self, digits: str) -> List[str]:
    if digits=='': return []
    ans = ['']
    tmp = []
    hmap={'2':'abc','3':'def','4':'ghi',
    '5':'jkl','6':'mno','7':'pqrs',
    '8':'tuv','9':'wxyz'
    }
    for num in digits:
        while(ans):
            cur = ans.pop()
            for option in hmap[num]:
                tmp.append(cur+option)
        ans = tmp
        tmp = []
    return ans
```

**hot011盛最多水的容器** *(11'28+{0})*
给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。
说明：你不能倾斜容器。

**解析:** 和003差不多一个类型.贪心初见杀.研究样例可以发现双指针,每次移动较短边一定可以找到容纳最多水的区域.

**标签:**[双指针],[滑动窗口],[偏易],[贪心]

```python
def maxArea(self, height: List[int]) -> int:
    n = len(height)
    left = 0
    right = n-1
    ans = min(height[left],height[right])*(right-left)
    while(left<right):
        if height[left]<height[right]:
            left+=1
        else:
            right-=1
        tmp = height[left]*(right-left) if height[left]<height[right] else height[right]*(right-left)
        if ans<tmp: ans=tmp
    return ans
```

**hot003无重复字符的最长子串** *(10'58+{0})*
给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。

**解析:** 双指针的滑窗.用哈希表记录当前窗口内的字符.时间和空间均O(n).贪心依据比较难想.比较好的破解是根据样例代码笔笔划划.

**标签:** [双指针],[滑动窗口],[偏易],[贪心]

```python
def lengthOfLongestSubstring(self, s: str) -> int:
    '''sliding windows
    '''
    if s == "": return 0
    n = len(s)
    hmap = set(s[0])
    st,ed = 0,0
    ans = 1
    while(ed<n-1):
        ed+=1
        while(s[ed]in hmap):
            hmap.remove(s[st])
            st+=1
        hmap.add(s[ed])
        if ed-st+1>ans: ans = ed-st+1
    return ans
```

**1&02归并排序** *2.(03_06)*

```python
#03_06重新审视了02_23的实现方法,由于左遍历返回记录的数组在右遍历的时候不会被释放,虽然仍然是ON的时间和空间,但这样的写法更优一些.因为每层确保没有下层层的时候在生成临时数组)
def sortArray(self, nums: List[int]) -> List[int]:
    '''归并排序
    '''
    def merge(arr,st,ed):
        if st>=ed: return 
        mid = (ed+st)//2
        merge(arr,st,mid)
        merge(arr,mid+1,ed)
        #起始这里还可以优化,不需要开辟临时数组,唯一需要开辟的数组就是arr
        #不过并不会改变时间复杂度
        a = arr[st:mid+1]
        b = arr[mid+1:ed+1]
        ans = []
        na,nb = len(a),len(b)
        sta,stb = 0,0
        while(sta<na and stb<nb):
            if a[sta]<=b[stb]:
                ans.append(a[sta])
                sta+=1
            else:
                ans.append(b[stb])
                stb+=1
        if sta<na:
            ans.extend(a[sta:])
        else:
            ans.extend(b[stb:])
        arr[st:ed+1]=ans
    merge(nums,0,len(nums)-1)
    return nums

#02_23整理之后的归并排序
def dfs1(left,right,nums):
    if left==right: return [nums[left]]

    if left>right: return []
    mid= (right+left)//2
    mg1 = dfs1(left,mid,nums)
    mg2 = dfs1(mid+1,right,nums)
    p1,p2,tmp=0,0,[]
    while(p1<len(mg1) and p2<len(mg2)):
        if mg1[p1]<mg2[p2]:
            tmp.append(mg1[p1])
            p1+=1
        else:
            tmp.append(mg2[p2])
            p2+=1
    tmp = tmp + mg1[p1:] if p1<len(mg1) else tmp+mg2[p2:]
    return tmp
```

```python
#注意,切片会产生额外的内存消耗
#下面代码是切片和不切片内存消耗的比较
from memory_profiler import profile
import time
global flag1
flag1=0
global flag2
flag2=0
def dfs1(left,right,nums):
    global flag1
    if left==right: 
        if flag1==0:
            print('A：%.2f MB' % (psutil.Process(os.getpid()).memory_info().rss / 1024 / 1024))
            flag1=1
        return [nums[left]]

    if left>right: 
        if flag1==0:
            print('A：%.2f MB' % (psutil.Process(os.getpid()).memory_info().rss / 1024 / 1024))
            flag1=1
        return []
    mid= (right+left)//2
    mg1 = dfs1(left,mid,nums)
    mg2 = dfs1(mid+1,right,nums)
    p1,p2,tmp=0,0,[]
    while(p1<len(mg1) and p2<len(mg2)):
        if mg1[p1]<mg2[p2]:
            tmp.append(mg1[p1])
            p1+=1
        else:
            tmp.append(mg2[p2])
            p2+=1
    tmp = tmp + mg1[p1:] if p1<len(mg1) else tmp+mg2[p2:]
    return tmp

def dfs2(nums):
    global flag2
    if not nums: 
        if flag2==0:
            print('A：%.2f MB' % (psutil.Process(os.getpid()).memory_info().rss / 1024 / 1024))
            flag2=1
        return []
    if len(nums)==1: 
        if flag2==0:
            print('A：%.2f MB' % (psutil.Process(os.getpid()).memory_info().rss / 1024 / 1024))
            flag2=1
        return nums
    mid= len(nums)//2
    mg1 = dfs2(nums[:mid])
    mg2 = dfs2(nums[mid:])

    p1,p2,tmp=0,0,[]
    while(p1<len(mg1) and p2<len(mg2)):
        if mg1[p1]<mg2[p2]:
            tmp.append(mg1[p1])
            p1+=1
        else:
            tmp.append(mg2[p2])
            p2+=1
    tmp = tmp + mg1[p1:] if p1<len(mg1) else tmp+mg2[p2:]
    return tmp


nums = [x for x in range(500000,0,-1)]
st1 = time.time()
ans1 = dfs1(0,len(nums)-1,nums)
ed1 = time.time()

st2 = time.time()
ans2 = dfs2(nums)
ed2 = time.time()

print((ed2-st2)-(ed1-st1))
```

##### 02_22

offerII:0_04(12'11+{1}),0I05(10'41+{0}),0II05(33'+{2}+{2.5}),006(4'50+{0}),007(21'05+{0})
**offerII0II06排序数组中两个数字之和** *(4'50+{0})*
给定一个已按照 升序排列  的整数数组 numbers ，请你从数组中找出两个数满足相加之和等于目标数 target 。
函数应该以长度为 2 的整数数组的形式返回这两个数的下标值。numbers 的下标 从 0 开始计数 ，所以答案数组应当满足 0 <= answer[0] < answer[1] < numbers.length 。
假设数组中存在且只存在一对符合条件的数字，同时一个数字不能使用两次。类似于hot0-01,但hot0-01需要额外排序,或者哈希.

**解析:**双指针

**标签:**[容易],[双指针],[数组]

```python
def twoSum(self, numbers: List[int], target: int) -> List[int]:
    n = len(numbers)
    left=0
    right=n-1
    while(left<right):
        cur = numbers[left]+numbers[right]
        if cur==target:
            return [left,right]
        elif cur>target:
            right-=1
        else:
            left+=1
```

**offerI0I05(替换空格)** *(10'41+{0})*
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

**解析:**python不能原地修改字符串.对python切片的理解:直接对变量(字符/列表)切片赋值,会修改元量.先用一个引用指向切片再进行操作,会新建一个变量,不会修改原变量.所有函数传递都包含了一个传参的过程,相当于有一个局部引用指向切片,因此会新建一个变量.总结:切片只有直接修改才会改变原变量,其余操作都会新建一个变量.另外一些知识包括:*1.对原变量的任意引用进行append/reverse/pop一定会修改原变量. 2.对原变量的任意引用进行+操作一定会新建变量.3.对切片直接赋值会修改原变量,对原变量切片增加新引用会创建新数组. 4.函数传递相当于创建一个新引用指向原变量,即切片会再函数中创建新数组,而不切片在函数中的append可以改变原数组 *

**标签:**[容易],[字符串]

```python
def replaceSpace(self, s: str) -> str:
    if s=='':return ''
    i = 0
    while(True):
        n = len(s)
        if i==n: break
        if s[i]==' ':
            s = s[:i]+'%20'+s[i+1:]
            i+=2
        i+=1
    return s
```

**0II05(318)最大单词长度乘积** *1.(02_22 33'+{2}+{2.5})* *2.(03_23 37'48+{0}+{2.5})*
给定一个字符串数组 words，请计算当两个字符串 words[i] 和 words[j] 不包含相同字符时，它们长度的乘积的最大值。假设字符串中只包含英语的小写字母。如果没有不包含相同字符的一对字符串，返回 0。

**解析**:(03_23)第二次做比第一次做花的时间还长.从'单词含有公共字母'这一点想到要用 位运算 .位运算一般都是用来快速比较两个数/两个单词是否一样(从26*26变成了1*1的时间复杂度.)

为了避免每次都要逐个字母比较单词,对所有单词进行二进制编码.然后按照长度进行从大到小排序,然后依次进行比较.看到位运算才想到了解题思路.在进行二进制编码的时候没有考虑重复数字,造成了一次错误.利用数组lambda表达式进行从大到小排序.还有一个减枝策略是,相同的编码只保留长度最长的.

> - lambda表达式:
>   只有一行的函数全部可以转换成lambda表达式的形式. 表达式的含义为 `lambda 输入:输出` eg.
>
> ```python
> def f(x):
>   return x*x
> ```
>
> 转换成lambda表达式为 `lambda x: x*x`
>
> - a.sort(key=?)
>   key里面传的就是lambda表达式(或者某个函数),输入固定为x,表示a中的元素,输出就是排序的依据 `<br>`
>   eg:1.按倒序排列:`a.sort(key=lambda x:-x)`, 2.按第二个元素排列:`a.sort(key=lambda x:x[1])`

**标签**:[位运算],[数组],[偏难]

```python
def maxProduct(self, words: List[str]) -> int:
    nword = []
    hmap = {}
    for word in words:
        tmp = 0
        n = len(word)
        word = set(word)
        for letter in word:
            tmp+=2**(ord(letter)-97)
        if tmp in hmap:
            if hmap[tmp][0]<n:
                bj = hmap[tmp][1]
                nword[bj][0]=n
                hmap[tmp][0]=n
        else:
            hmap[tmp]=[n,len(nword)]
            nword.append([n,tmp])
    nword.sort(key = lambda x: (-x[0],x[1]))
    ans = 0
    n = len(nword)
    for i in range(n):
        li = nword[i][0]
        if li**2<=ans: break
        for j in range(i+1,n):
            lj = nword[j][0]
            if li*lj<=ans: break
            if nword[i][1] & nword[j][1] ==0:
                ans=li*lj
    return ans
```

**0II04(137)只出现一次的数字** (12'11+{1}) (07_12){11'03}
给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。

**解析:**位运算的两个知识点:1.a右移一位 `a=a>>1`,2.判断a的最低位是不是1 `a&1==1`. 还有一些扩充的:去除a的最右端1后的值 `a=a&(a-1)` 取出a的位级表示中最低的那一位 `a=a&(-a)` [*由于负数存的是补码,因此这两个操作只对n>=0有效*]对位运算不熟悉导致了耗时长,忽略了shuwei操作导致了做错一次.

**解析:**[数组],[位运算],[中等]

```cpp
    int singleNumber(vector<int>& nums) {
        vector<int>shuwei(32,0);
        int fuhao=0,wei=0;
        for(ll elem:nums){
            int ct=0;
            if(elem<0){elem*=-1;fuhao++;}
            while(elem>=1){
                wei=elem%2;
                shuwei[ct]+=wei;
                ct++;
                elem/=2;
            }
        }
        ll num=0,ct=1;
        for(int i=0;i<32;i++){
            if(shuwei[i]%3==1)num+=ct;
            ct*=2;
        }if(fuhao%3==1){num*=-1;}
        return int(num);
    }
```

```python
def singleNumber(self, nums: List[int]) -> int:
    #记录nums中所有数字的数位之和
    #利用fuhao记录符号位,符号是3的倍数说明目标是正数,否则是负数
    shuwei = [0]*32
    fuhao = 0
    for num in nums:
        if num<0:
            fuhao+=1
            num*=-1
        ct = 0
        while(num):
            if num & 1 == 1:
                shuwei[ct]+=1
            num = num>>1
            ct+=1

    ans=0
    for ind in range(32):
        if shuwei[ind]%3 == 1:
            ans+=2**ind
    if fuhao%3==1:
        ans*=-1
    return ans
```

##### 02_21

因为面试要占用时间,而且面试也会要求做题.所以就做两道题就可以了.两道单调栈的题.
hot ~~581~~,~~739~~; 学习快速排序和,~~hot134~~(面试考到了)

**hot134:加油站**
在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
给定两个整数数组 gas 和 cost ，如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。

**解析:**四维纵横一面面试题,没做出来on的解,挂了.正解是贪心,通过合并加油站的思路可以确定如果sum(gas)>sum(cost)的话,一定可以遍历.同时,如果从i最远走到j,那么j也必然走不到j+1,同理i..j中没有可以做起点.所以从j+1开始继续判断.一直判断到最后即可.

```python
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        '''这道题关键时要分析出总油量>总消耗的话,一定可以跑完
        '''
        sumgas = 0
        sumcost = 0
        n = len(gas)
        rest=0
        st=0
        for i in range(n):
            rest+=(gas[i]-cost[i])
            sumgas+=gas[i]
            sumcost+=cost[i]
            if rest<0:
                rest=0
                st=i+1
        if sumgas-sumcost<0:return -1
        else: return st
```

**1&01快速排序(hot912)** *2.(03_06)* *3.(04_02) CPP*

**解析:**思路是分治+递归.考虑重复数的描述是:左边都是>=它的数,右边都是<=它的数.

```python
##(03_06)解决了基本有序和基本一致数组退化的写法
def sortArray(self, nums: List[int]) -> List[int]:
    import random
    def qs(arr,st,ed):
        if st>=ed : return
        rdc = random.randint(st,ed)
        arr[st],arr[rdc]=arr[rdc],arr[st]
        left,right = st,ed
        while(left<right):
            while(arr[left]<arr[right] and left<right):
                right-=1
            arr[left],arr[right] = arr[right],arr[left]
            if left<right : left+=1
            while(arr[left]<arr[right] and left<right):
                left+=1
            arr[left],arr[right] = arr[right],arr[left] 
            if left<right : right-=1
        qs(arr,st,left-1)
        qs(arr,left+1,ed)
    qs(nums,0,len(nums)-1)
    return nums

#这样的写法是标准的快速排序.但面对基本有序[1,2,3,4,5]数组和基本一致数组[2,2,2,2,2]会退化成O(N2).
#增加随机选取初始点可以解决基本有序退化,每次一致性都交换并且后移以为可以解决基本一致.
def dfs(nums,l,r):
    if l>=r: return #如果是首元素或者最后一个元素分割,会出现l>r的情况,因此不能用等号判断
    cur = nums[l]
    st,ed = l,r
    while(st<ed):
        #如果没有等号那么cur就会被重复数先限制住
        #等号表示它右边都是大于等于它的,左边都是小等于它的不会报错
        while(cur<=nums[ed] and st<ed):
            ed-=1
        nums[st],nums[ed] = nums[ed],nums[st]
        while(cur>=nums[st] and st<ed):
            st+=1
        nums[st],nums[ed] = nums[ed],nums[st]
  
    ll,lr = l,st-1
    rl,rr = st+1,r
    dfs(nums,ll,lr)
    dfs(nums,rl,rr)

a = [5,7,4,4,4,6,3,1,4,4,2,9,8]
# a = [5,6]
dfs(a,0,len(a)-1)
print(a)
```

**hot739:每日温度**
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

**解析:**如果只存储序号,可以优化空间,但是增加思考的难度.

**标签:**[单调栈]

**hot581:最短无序连续子数组** *2.(03_23)26'04+{1}*
给你一个整数数组 nums ，你需要找出一个 连续子数组 ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
请你找出符合题意的 最短 子数组，并输出它的长度。

**解析:**(03_23)这次用了单调栈解决.代码量减少了,但是空间复杂度增加了.
双指针分别确定左右边界,注意1.只有从来没遇到过更大的数的时候左边界才会增长.
2.要考虑想等的数的情况.

**标签:**[分析],[数组],[双指针]

```python
def findUnsortedSubarray(self, nums: List[int]) -> int:
    '''哪他吗有什么单调栈,臭傻逼,双指针
    '''
    n = len(nums)
    left = float('-inf')
    lind = -1
    right = float('inf') 
    rind = n
    for ll in range(n):
        if ll-lind==1 and nums[ll]>=left:
            lind = ll
            left = nums[ll]
        else :
            while(nums[ll]<left):
                lind-=1
                if lind<0: break
                left = nums[lind]
            if lind<0:break
    if lind==n-1: return 0
    for rr in range(n-1,-1,-1):
        if rr-rind==-1 and nums[rr]<=right:
            rind = rr
            right = nums[rr]
        else:
            while(nums[rr]>right):
                rind+=1
                if rind>n-1: break
                right = nums[rind]
            if rind>n-1:break
    return rind-lind-1

def findUnsortedSubarray(self, nums: List[int]) -> int:
    stack = []
    st,ed = float('inf'),float('-inf')
    maxn = float('-inf')
    for idx,num in enumerate(nums):
        while(stack and num<stack[-1][0]):
            _,ids = stack.pop()
            if ids < st:st = ids

        if num<maxn: ed = idx
        else: maxn=num

        stack.append((num,idx))

    if st==float('inf'): return 0
    else: return ed-st+1
```

##### 02_18

**015三数之和**
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请
你返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。

**解析:** sort+双指针+对于重复元素进行过滤减枝,两数之和升级版,考虑重复数很大增加了难度

**标签:**[数组],[双指针],[偏难]

```python
def threeSum(self, nums: List[int]) -> List[List[int]]:
    '''按照两数之和，是o(n2)复杂度,
    这时可以用sort进行剪枝,因为sort时nlogn的
    对元组重复也要进行判断
    '''
    from collections import defaultdict
    nums.sort()
    n = len(nums)
    hmap = defaultdict(int)
    ret = []
    for i in range(n):
        hmap[nums[i]]+=1
  
	def check(i,j,k):
        if i!=j and j!=k: return True
        if i==j and j==k:
            if hmap[i]>=3: return True
            else: return False
        if i==j:
            if hmap[i]>=2: return True
            else: return False
        if j==k:
            if hmap[j]>=2: return True
            else: return False

    for i in range(n):
        if i>0 and nums[i]==nums[i-1]: continue
        if nums[i]>0 : 
            return ret
        jprev=None
        for j in range(i+1,n):
            if j>1 and nums[j]==jprev: continue
            if (0-nums[i]-nums[j]) <nums[j]: break
            if (0 - nums[i]-nums[j]) in hmap:
                if check(nums[i],nums[j],0-nums[i]-nums[j]):
                    ret.append([nums[i],nums[j],0-nums[i]-nums[j]])
            jprev = nums[j] 
    return ret
```

**001两数之和** *02_28 15'+{0}*

**解析:**对于无序数列,要么sort(logn)变有序然后双指针(on).要么哈希(on)然后遍历(on)

**标签:**[数组],[容易]

```python
#哈希版
def twoSum(self, nums: List[int], target: int) -> List[int]:
    from collections import defaultdict  
    tar = target
    hmap = defaultdict(list)
    for idx, num in enumerate(nums):
        hmap[num].append(idx)

    for num in nums:
        if len(hmap[tar-num])==0: continue
        if tar-num==num: 
            if len(hmap[tar-num])==1: continue
            else: return [hmap[num][0],hmap[num][1]]
        else:
            return [ hmap[num][0],hmap[tar-num][0] ]  
```

##### 02_17

树+递归!
offerI ~~26~~, ~~32-3~~, ~~34~~, ~~36~~

**0I36二叉搜索树与双向链表** *(07_12){29'}*
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。

**解析**:和114/897有点像,只不过114只要先序遍历,这里要求排序的话只能中序遍历展开,复杂一点.897只要求但链表,这里双链表最后还要最后一个节点和首节点相连,麻烦一点.但只要会写递推版的中序遍历,这个展开还是好展开的.

**标签**:[二叉树],[递推],[中序遍历],[中等]

```cpp
Node* treeToDoublyList(Node* root) {
    vector<Node*>stack;
    Node * prev=NULL,*cur=NULL,*head=NULL;
    unordered_map<Node*,int>hmap;
    if(root==NULL)return root;
    stack.emplace_back(root);
    int ct=0;
    while(stack.size()){
        while(stack.back()->left!=NULL and hmap[stack.back()->left]==0){
            cur=stack.back()->left;
            stack.emplace_back(cur);}
        if(head==NULL)head=stack.back();
        cur=stack.back();
        stack.pop_back();
        hmap[cur]=1;
        if(prev!=NULL){prev->right=cur;cur->left=prev;}
        prev=cur;
        if(cur->right!=NULL){stack.emplace_back(cur->right);}
    }
    head->left=cur;cur->right=head;
    return head;
}
```

```python
def treeToDoublyList(self, root: 'Node') -> 'Node':
    '''递推前序遍历中加加点操作
    '''
    if not root: return None
    stack = [root]
    vis = set()
    prev = None
    head = None
    while(stack):
        top = stack[-1]
        while top.left and top.left not in vis:
            top = top.left
            stack.append(top)
        top = stack.pop()
        vis.add(top)
        if prev: prev.right = top
        else: head = top
        top.left = prev
        prev = top
        if top.right:
            stack.append(top.right)
    head.left = prev
    prev.right = head
    return head
```

**offerI0I34二叉树中和为某一值的路径**

**解析**:递归,注意审题,是从根节点到叶子节点.

**标签**:[二叉树],[递归],[偏易]

```python
def pathSum(self, root: TreeNode, target: int) -> List[List[int]]:
    '''审题,是从根节点到叶子节点的路径,而不是中间随便一条子路径
    '''
    self.ret = []
    tar = target
    def dfs(root,cur_list,cur_val,tar):
        if root == None: return 
        cur_val += root.val
        cur_list.append(root.val)
        if not root.left and not root.right and cur_val==tar:
            self.ret.append(cur_list.copy())
            cur_list.pop()
            return 
        dfs(root.left, cur_list, cur_val,tar)
        dfs(root.right, cur_list, cur_val, tar)
        cur_list.pop()
        return
    dfs(root,[], 0, tar)
    return self.ret
```

**0I32-III 从上到下打印二叉树**
请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

**解析**:(0708)这道题最大的问题是不能总想着节省,要话一个辅助队列来储存当前的入队\出队元素.如果只用一个队列,队列中有元素没有清空会造成麻烦.
这道题在构思的时候一开始没想明白,后来发现起始和中序遍历比起来只用改一个地方,就是进栈顺序.实际顺序是:如果当前层从左向右,则进栈为先左后右,保证下一层是从右向左.如果当前层从右向左,则进展从右向左,保证下一层是从左向右.说起来有点绕,但实际那例子比或以下就行.

**标签**:[二叉树],[中等],[层序遍历]

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#define TN TreeNode
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        deque<TN*>stack0; TN*tmp;
        deque<TN*>stack1;
        vector<vector<int>>ans;
        vector<int>arr;
        if(not root){return ans;}
        stack0.emplace_back(root);
        int n=stack0.size();
        while(n){
            for(int i=0;i<n;i++){
                tmp=stack0.back();stack0.pop_back();arr.emplace_back(tmp->val);
                if (tmp->left) {stack1.emplace_back(tmp->left);}
                if (tmp->right){stack1.emplace_back(tmp->right);}
            }if(arr.size()){ans.emplace_back(arr);}arr.clear();n=stack1.size();
            for(int i=0;i<n;i++){
                tmp=stack1.back();stack1.pop_back();arr.emplace_back(tmp->val);
                if (tmp->right) {stack0.emplace_back(tmp->right);}
                if (tmp->left){stack0.emplace_back(tmp->left);}
            }if(arr.size()){ans.emplace_back(arr);}arr.clear();n=stack0.size();
        }
        return ans;
    }
};
```

```python
def levelOrder(self, root: TreeNode) -> List[List[int]]:
    if not root: return []
    ret = []
    cur_lay = [root]
    nex_lay = []
    cur_val = []
    flag = 'left'
    while(cur_lay):
        cur = cur_lay.pop()
        cur_val.append(cur.val)
        if flag=='left':
            if cur.left: nex_lay.append(cur.left)
            if cur.right: nex_lay.append(cur.right)
        else:
            if cur.right: nex_lay.append(cur.right)
            if cur.left: nex_lay.append(cur.left)
        if not cur_lay:
            ret.append(cur_val)
            cur_lay = nex_lay
            nex_lay = []
            cur_val = []
            flag = 'left' if flag=='right' else 'right'
    return ret
```

**offerI026(树的子结构)**
输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
B是A的子结构， 即 A中有出现和B相同的结构和节点值。

**解析**: 思路挺直白的,遍历A(先序就可以了,刚刚发现平时想的最简单递归起始一般就是先序了,只不过没有仔细思考过定义而已.).然后对A中的每一个节点都和B进行匹配.说起来满,但一般头几个就会匹配不上.所以对题目样例来说速度还可以.

**标签**: [二叉树],[偏易],[先序遍历]

```python
'''遍历+判断
'''
def isSubStructure(self, A: TreeNode, B: TreeNode) -> bool:
    if not B: return False
    def dfs(A,B):
        if not A: return False
        if self.check(A,B): return True
        return (dfs(A.left,B) or dfs(A.right,B))
    return dfs(A,B)

def check(self, A, B):
    if (not A and not B) or not B: return True
    if not A: return False
    if A.val != B.val: return False
    return self.check(A.left,B.left) and self.check(A.right,B.right)
```

##### 02_16

**hot236二叉树的最近公共祖先**  *03_06 20'39+{0}* *(06_24){50'}+{0}+{5}*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

**解析**:03_06:写了一种递归,但代码比参考的递归复杂一些.仍然是保证了找到节点之后立刻返回.和参考答案的递归解空间不一致但没有熟优熟劣只分别.记住我这种递归就可以了. 最直观想法:用dfs搜到两个节点的祖先列表,比较该列表找到最深公共最先. 但有一种递归表述:一棵树,如果左,右子树都没有关键节点,就返回空,如果左右子树都有关键节点,那当前节点就是最深根节点,返回当前节点.如果左子树有关键点右子树没有,那么要么改关键节点就是最深根节点,要么上层可以找到最深根节点,返回左子树的节点.但这种写法真的很难想.

**标签**:[二叉树],[中等],[递归]

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* ans = dfs(root,p->val,q->val);
    return ans;
}

TreeNode* dfs(TreeNode* rt,int p, int q){
    if (rt==nullptr) return rt;
    if (rt->val==p or rt->val==q) return rt;
    TreeNode* left = dfs(rt->left,p,q);
    TreeNode* right = dfs(rt->right,p,q);
    if(left and right) return rt;
    if(left) return left;
    if (right) return right;
    return nullptr;
}
```

```python
#递归解法
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        '''这种写法和参考答案里的递归搜索区域不一样,但是都保证是正确的
        '''
        ans = []
        def dfs(k):
            if not k : return False
            left = dfs(k.left)
            if ans: return False
            right = dfs(k.right)
            if ans: return False
            if (left and right):
                ans.append(k)
                return False
            if k == p or k==q:
                if left or right: 
                    ans.append(k)
                    return False
                return True
            elif left or right:
                return True
            else:
                return False
        dfs(root)
        return ans[0]
#搜索解法
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        '''一开始我只能想到先用深搜把两个目标节点的祖先列表给搜出来,
        然后挨个比对看最近的公共最先是那个
        '''
        self.root_dic = {'p':None,'q':None}
        self.flag=0
        def dfs(root,root_list):
            if not root: return 
            if self.flag==2: return

            root_list.append(root)
            if root == p:
                self.root_dic['p'] = root_list.copy()
                self.flag+=1
            if root == q:
                self.root_dic['q'] = root_list.copy()
                self.flag+=1
  
            dfs(root.left,root_list)
            dfs(root.right,root_list)
            root_list.pop()
            return 
        dfs(root,[])
        p_lis = self.root_dic['p']
        q_lis = self.root_dic['q']
        if len(p_lis)>len(q_lis) : p_lis,q_lis=q_lis,p_lis
        for i in range(len(p_lis)):
            if p_lis[i]!=q_lis[i]: return p_lis[i-1]
        return p_lis[-1]
```

**hot226翻转二叉树**
给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。

**解析**:递归表述:要想翻转一个二叉树,只需要分别翻转根节点所对应的左右子树.

**标签**:[二叉树],[递归],[容易]

```python
def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
    def dfs(root):
        if not root: return root
        if not root.left and not root.right:
            return root
        root.left , root.right = dfs(root.right), dfs(root.left)
        return root
    return dfs(root)
```

**hot114二叉树展开为链表**
给你二叉树的根结点 root ，请你将它展开为一个单链表：
    展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
    展开后的单链表应该与二叉树 先序遍历 顺序相同。

**解析**:修改一点的前序遍历.每次记住当前节点的前趋节点.然后修改前趋节点的指向.~~这个只有先序遍历可以这样改.~~ 中序遍历后序应该都可以,因为遍历过的节点才会成为前趋才会被修改,而遍历过的节点被修改没关系.

**标签:**[二叉树],[先序遍历],[偏易]

**hot105从前序与中序遍历序列构造二叉树** *2.(03_21) {22'12}+{0}* *(06_04) {1'53}+{0}+{0}*
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

**解析**:(03_21)有一个优化没注意到,预先进行哈希处理可以让每次深搜中oN找坐标的复杂度变成O1(总体从ON2变成ON)  但差一点完美,如果外面用哈希记录中序的数字和下标对应,则递归中可以避免每次都要对中序列表的一个子集进行搜索,大幅减少时间消耗.
这道题的最佳递归方案在于:可以通过前序遍历确定根(首元素为根),中序遍历确定左右子树.这样可以递归的得到左右子树的前序遍历和中序遍历.这样递归的可以构造出整个树.但每次dfs往下层传递都要传递子树的那一部分.如果传列表会占用很多空间(这说明每次传递的不是列表引用吗?虽然每层修改的是同一个链表,但是应该还是有复制的过程),最省时间和空间的方式还是传pointer.

**标签**:[递归],[二叉树],[中等],[掌握]

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 #define vit vector<int>
class Solution {
public:
    int i;
    unordered_map<int,int> map;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode * rt=nullptr;
        int n = preorder.size()-1;
        if (n<0) return rt;
        hash(inorder,n);
        rt = dfs(preorder,inorder,0,n,0,n);
        return rt;
    }
    void hash(vit&in,int n){
        map.reserve(n);
        for (i=0;i<=n;i++){
            map[in[i]]=i;
        }
    }

    TreeNode * dfs(vit&pre, vit&in, const int pre_st,const int pre_ed, const int in_st, const int in_ed){
        if (pre_ed - pre_st<0)return nullptr;
        TreeNode& root = *(new TreeNode(pre[pre_st]));
        int lft_pre_st,lft_pre_ed,lft_in_st,lft_in_ed;
        int rt_pre_st,rt_pre_ed,rt_in_st,rt_in_ed;
        lft_pre_st = pre_st+1;  int mid=-1;

        mid = map[pre[pre_st]];

        // for (i=in_st;i<=in_ed;i++){
        //     if(in[i]==pre[pre_st]){
        //         mid=i;break;            } }

        lft_in_st = in_st;  rt_in_st = mid+1;
        lft_in_ed = mid-1;  rt_in_ed = in_ed;
        int lft_scle = mid-1-in_st;
        lft_pre_ed = lft_scle+lft_pre_st;
        rt_pre_st = lft_pre_ed+1; rt_pre_ed = pre_ed;
        
        // cout<<lft_pre_st<<" "<<lft_pre_ed<<" "<<lft_in_st<<" "<<lft_in_ed<<endl;
        
        root.left = dfs(pre,in,lft_pre_st,lft_pre_ed,lft_in_st,lft_in_ed);
        root.right = dfs(pre,in,rt_pre_st,rt_pre_ed,rt_in_st,rt_in_ed);

        return &root;
    }
};
```

```python
def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
    '''
    这方法递归的构造解是真的简洁!注意,如果前序和中序的信息都需要递归中更新
    '''
    hmap = {}
    n = len(inorder)
    for i in range(n):
        hmap[inorder[i]]=i
  
    def dfs(stp,edp,sti,edi):
        if stp>edp: return None 
        if stp==edp : 
            return TreeNode(preorder[stp])
        root = TreeNode( preorder[stp] )
        idx = hmap[preorder[stp]]
  
        lsti,ledi = sti,idx-1
        rsti,redi = idx+1,edi
        llen = ledi-lsti+1
        rlen = redi-rsti+1
        lstp,ledp = stp+1,stp+llen
        rstp,redp = stp+llen+1,edp
  

        root.left = dfs(lstp,ledp,lsti,ledi)
        root.right = dfs(rstp,redp,rsti,redi)
        return root

    root = dfs(0,n-1,0,n-1)
    return root
```

##### 02_15

**hot102二叉树的层序遍历** *(06_24){16'55}+{0}+{0}*
给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

**解析**:用一个额外队列记录下一层信息,可以每次都读取一层的节点组成一个列表.如果只用一个队列的话判断层不很方便(每次传元素要把层信息传进去,而且还要专门判断层是不是增加了).两个队列比较优雅

**标签**:[二叉树],[遍历],[中等],[掌握]

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    queue<TreeNode*> que; //que.reserve(200_0);
    vector<vector<int>>ans; ans.reserve(200_0);
    vector<int> tmp; tmp.reserve(200_0);
    if (root==nullptr)return ans;
    TreeNode * tnd;
    que.push(root);
    while(que.size()){
        int n = que.size();
        for(int i=1;i<=n;i++){
            tnd = que.front();
            que.pop();
            if (tnd->left) que.push(tnd->left);
            if (tnd->right) que.push(tnd->right);
            tmp.emplace_back(tnd->val);
        }ans.emplace_back(tmp);tmp.clear();
    }return ans;
}
```

```python
def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
    '''我记得之前是每次都要记主当前layer,当layer转换的时候,开始新记一行
    这次优雅了一点,有了两个数组,当一个数组读完之后,就证明这一层读取完毕,把这[tmp数组里
    的数据添加进ret里面,然后开始记新的一行
    '''
    from collections import deque
    if not root: return []
    queue = deque([root])
    tmpque = deque([])
    tmpval = []
    ret = []
    while(True):
        if not queue and not tmpque: 
            ret.append(tmpval)
            break
        if not queue: #这一层数据读完了
            queue = tmpque
            tmpque = deque([])
            ret.append(tmpval) 
            tmpval = []
        cur = queue.popleft()
        if cur.left: tmpque.append(cur.left)
        if cur.right: tmpque.append(cur.right)
        tmpval.append(cur.val)
    return ret
```

**1&04二叉树的先中后序遍历** (144,94,145)
*03_31:*
只写了后序遍历,虽然时间上多了一点,但理解应该是更好的.因为这次是直接写后序,而且包括了写递归的时间.对后序遍历,最优的就是vis代表添加到ans里的点.如果用vis代表访问过左值的点,也可以做,但是会麻烦一点. 中序遍历的vis亦如是,代表添加到ans里的点可以得到最优代码.

*03_17::*
前序 *2'13+{0} and 17'07+{1}*
中序 *2'13+{0} and 10'13+{0}*
后序 *0'53+{0} and 15'02+{0}*  * 3.(03_31 18'54+{0}) * *4.(04_11) 52'+{0} CPP*
(是话说,虽然都写出来了,但是离快速处理还差一点)
先/中/后序遍历*递归/递推六个代码
[目前掌握的很好了]
规律总结:对于递归,只需要改动添加的当前节点值进返回列表的位置即可.
对于递推:前序遍历因为先访问根节点,不会存在访问完左(右)子树访问根节点的时候有要访问左右子树的问题,因此不需要用vis记录.中序需要记录左子树,因为左子树完之后还会访问根节点.后续左右子树都要记录.对前序遍历因为栈结构特点,要记得先push右儿子再push左儿子才能先遍历到左子树.

```python
#递归先序遍历二叉树
def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
    ret = []
    def dfs(root):
        if not root: return
        ret.append(root.val)
        dfs(root.left)
        dfs(root.right)
        return
    dfs(root)
    return ret

#递归中序遍历二叉树
def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
    ret = []
    def dfs(root):
        if not root: return
        dfs(root.left)
        ret.append(root.val)
        dfs(root.right)
        return
    dfs(root)
    return ret

#递归后续遍历二叉树
def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
    ret = []
    def dfs(root):
        if not root: return 
        dfs(root.left)
        dfs(root.right)
        ret.append(root.val) 
        return
    dfs(root)
    return ret

#迭代先序遍历二叉树
def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
    ret = []
    stack = []
    #考虑没有节点的情况
    if root : stack.append(root)
    while(stack):
        cur = stack.pop()
        ret.append(cur.val)
        #要反序入栈
        if cur.right:
            stack.append(cur.right)
        if cur.left:
            stack.append(cur.left)
    return ret

#迭代中序遍历二叉树
def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
    vis = set()
    ret = []
    stack = []
    if root: stack.append(root)
    while(stack):
        top = stack[-1]
        while top.left and top.left not in vis:
            stack.append(top.left)
            top = top.left

        stack.pop()
        vis.add(top)
        ret.append(top.val)
  
        if top.right:
            stack.append(top.right)
    return ret

#迭代后序遍历二叉树
def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
    vis = set()
    ret = []
    stack = []
    if root : stack.append(root)
    while(stack):
        top = stack[-1]
        while(top.left and top.left not in vis):
            stack.append(top.left)
            top = top.left
        if (top.right and top.right not in vis):
            stack.append(top.right)
            continue #如果走了这一步,那其当前肯定不是可以添加的(因为右边还有东西)
                    #反之,如果右边没有东西了,或者右边东西都处理完了,那肯定就可以添加
                    #这真的是我写出来的吗tat好巧妙
        cur = stack.pop()
        vis.add(cur)
        ret.append(cur.val)
    return ret
```

```cpp
//迭代后序遍历二叉树
#define TN TreeNode
class Solution {
public:
    vector<int> arr;
    unordered_map <TN*,int>vis;
    vector<TN*> stack;
    TN* cur;
    vector<int> postorderTraversal(TreeNode* root) {
        if (not root) return arr;
        stack.push_back(root);
        while(stack.size()){
            cur = stack.back();
            while(cur->left and (vis.count(cur->left)==0)){
                stack.push_back(cur->left);cur = cur->left;}
            if (cur->right and (vis.count(cur->right)==0)){
                stack.push_back(cur->right);cur = cur->right;
            }else{
                stack.pop_back();vis[cur]=1;arr.push_back(cur->val);}
        }
        return arr;
    }
};
```

##### 02_14

做几道树的题吧
hot:~~094~~,~~096~~,~~098,101~~

**hot101对称二叉树**
给你一个二叉树的根节点 root ， 检查它是否轴对称。

**解析**:这道题用递归可以说是有快又简洁,本质上是先序遍历,左子树根-左-右对称的遍历右子树的根-右-左.对于有节点和没有节点的判断递归也是容易的.我最初的想法是分别对称的遍历左右子树,看看元素是不是相等.还特意写成了递推的形式.

**标签**:[二叉树],[序遍历],[偏易]

```python
#简单递归
def isSymmetric(self, root: Optional[TreeNode]) -> bool:
    '''递归的本质是先序遍历
    递归写法是真的简洁
    '''
    def dfs(left,right):
        if not left and not right: return True #都没有后序节点,符合对称条件
        if not left or not right: return False
        if left.val!=right.val:
            return False
        else:
            return dfs(left.left,right.right) and dfs(left.right,right.left)
    return dfs(root.left, root.right)

#麻烦递推形式
def isSymmetric(self, root: Optional[TreeNode]) -> bool:
    '''思路:分成左右两棵子树,左边按根-左-右遍历(节点位置也要遍历)
    这题本质上还是先序遍历,但看答案说递推形式比较容易,下次再写出递推形式的代码.
    '''
    self.lstack = [root.left]
    self.rstack = [root.right]
    while (self.lstack or self.rstack):
        lv = self.left_next()
        rv = self.right_next()
        if lv!=rv: return False
    # if (self.lstack or self.rstack): return False #一个空一个非空
    return True

def left_next(self):
    '''根-左-右
    '''
    if not self.lstack : return -101
    cur = self.lstack.pop()
    if not cur: #如果是空节点,直接返回
        return cur
    else:
        self.lstack.append(cur.right)
        self.lstack.append(cur.left)
        return cur.val
  

def right_next(self):
    '''根-右-左
    '''
    if not self.rstack : return -101
    cur = self.rstack.pop()
    if not cur: #如果是空节点,直接返回
        return cur
    else:
        self.rstack.append(cur.left)
        self.rstack.append(cur.right)
        return cur.val
```

**hot098验证二叉搜索树**  *2.(03_20) 15'55+{1}*
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
有效 二叉搜索树定义如下：
    节点的左子树只包含 小于 当前节点的数。
    节点的右子树只包含 大于 当前节点的数。
    所有左子树和右子树自身必须也是二叉搜索树。

**解析**:(03_20)这道题用递归做方法很自然,因为二叉搜索树本身定义就是递归的:左右子树分别是二叉搜索树.错的那次是判断树违规只考虑了左>根,根>右的情况,而没考虑左=根,根=右的情况.自测的话要想到用相等的测试样例.
这道题需要依靠一个有意思的结论:二叉搜索树<=>中序遍历是从小到大排列的.一开始我还想着要判断父结点,子结点之间的关系,但这样由需要递归的形式(有点像先序遍历的递归)(因为要记录子树的lower,higher,我总觉得改节点属性这种操作怪怪的,只有递归传递).后来看到我之前写的代码才意识到原来还有这样一个结论.和写递归复杂度是一样的应该.这道题值得用递归再做一遍.

**标签**:[二叉树],[序遍历],[偏难]

```python
def isValidBST(self, root: Optional[TreeNode]) -> bool:
    '''先写一个递推的中序遍历,
    然后组看是否是从小到大排序的.这是因为:
    一个树是二叉搜索树 <=> 一棵树中序遍历顺序是从小到大的
    二刷这道题价值还是比较大的:1.复习了三种遍历顺序的递推/递归写法
    2.对题意有了深刻认识
    以后做这种题如果不是告知了一定要递推,还是用递归吧,不容易写错
    '''
    vis = set()
    stack = [root]
    cur_val = float('-inf')
    while(stack):
        top = stack[-1]
        if top.left and top.left not in vis:
            stack.append(top.left)
            continue
  
        tmp = stack.pop()
        vis.add(tmp)
        if tmp.val>cur_val:
            cur_val = tmp.val
        else:
            return False

        if tmp.right :#and tmp.right not in vis:
            stack.append(tmp.right)
    return True

#递归解法,行数多一些,但思路很清晰:
def isValidBST(self, root: Optional[TreeNode]) -> bool:
    global flag
    flag = 1
    def dfs(root):
        global flag
        if flag==0: return [False]
        if not root: return [False]
        lft = dfs(root.left)
        if len(lft)==1:
            lft = [root.val-1,root.val-1]
            minv = root.val
        else:
            minv = lft[0]
  
        rt = dfs(root.right)
        if len(rt)==1:
            rt = [root.val+1, root.val+1]
            maxv = root.val
        else:
            maxv = rt[1]

        if lft[1]>=root.val or rt[0]<=root.val:
            flag=0
            return [False]
        else:
            return [minv,maxv]

    dfs(root)
    if flag==1: return True
    else: return False
```

**hot096不同的二叉搜索树**
给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。

**解析**:看似是二叉树的题,但实际是动归的题.难点在于状态转移方程不好写,涉及到两个状态空间.这是第一次遇到两个状态空间交替生成的这种状态转移.G[n],n个节点组成的二叉搜索树有多少种.F[i][n],以第i个节点为根,n个节点组成的二叉搜索树有多少种.但这种题没必要重复做,因为总结不出啥触类旁通的规律来.

**标签**:[动态规划],[困难]

```python
def numTrees(self, n: int) -> int:
    '''动态规划的困难题,这种状态转移方程想出来需要智商而不是经验吧
    '''
    G = [0]*(n+1)
    F = [[0]*(n+1)for x in range((n+1))]
    G[0],G[1]=1,1
    for m in range(2,n+1): #2...n
        for i in range(1,m+1): #1...m
            F[i][m]=G[i-1]*G[m-i]
            G[m]+=F[i][m]
    return G[n]
```

**hot094二叉树的中序遍历**
给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

**解析**:对于先,中,后三序遍历.递归要比递推好写一些.递推的时候先序遍历不需要设置vis哈希表(因为为先访问根节点,不会重复访问),中后序都需要有vis哈希表来记录,防止左/左右子树的重复遍历.对于这种遍历问题,能题归尽量写递归,除非名说不然用递归.因为这个序遍历的定义就时递归定义的.

**标签**:[二叉树],[序遍历],[容易]

```python
#递归版
def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
    '''递归很简单就解决了,三刷,能做出来就行了,没有递推的必要
    '''
    ret = []
    def dfs(cur):
        if not cur: #空节点,直接返回
            return
        dfs(cur.left)
        ret.append(cur.val)
        dfs(cur.right)
    dfs(root)
    return ret

#递推版
def isValidBST(self, root: Optional[TreeNode]) -> bool:
    vis = set()
    stack = [root]
    cur_val = float('-inf')
    while(stack):
        top = stack[-1]
        if top.left and top.left not in vis:
            stack.append(top.left)
            continue
  
        tmp = stack.pop()
        vis.add(tmp)
        if tmp.val>cur_val:
            cur_val = tmp.val
        else:
            return False

        if tmp.right :#and tmp.right not in vis:
            stack.append(tmp.right) 
    return True

#后续遍历的递推版,中序遍历也类似,只是pop(),以及vis的判断要针对
#性调整一下
def isValidBST(self, root: Optional[TreeNode]) -> bool:
    vis = set()
    stack = [root]
    while(stack):
        top = stack[-1] #栈顶元素
        if top.left and top.left not in vis:
            stack.append(top.left)
            continue
        if top.right and top.right not in vis:
            stack.append(top.right)
            continue
        cur = stack.pop()
        vis.add(cur)
        print(cur.val)
```

##### 02_13

今天就来搞清楚红黑树B+数原理,以及049的动归实现

- [X] 红黑树
  功能:查找某个数是否在某个数组中(二叉查找树)[但一个特殊功能是它可以在logn时间内查找数组中最小,最大元素(左端点和右端点),]
  为了避免AVL树在频繁插入删除下频繁调整自身耗时,提出红黑树.红黑树查找效率仍然是logn但插入删除不再频繁
- [X] 堆:
  堆只能查找数组(当前堆)中最小/最大的元素,不能查找指定元素是是否在堆中.
  [上滤],[下滤],插入删除都是logn
- [X] B+树
- [X] 49动归

##### 02_12

I:~~063~~,~~m013,060~~,049
**0I49(264)丑数** *2.(03_31) 14'05 + {0}* *(06_24){12'}+{0}+{0}*
我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。

**解析**:(03_31) 关键在于最小值可以由2,3,5的因子队列递推得到.
比较容易能想到的是小根堆+哈希.利用小根堆每次logn的查找用时,总复杂度在nlogn.但其实这题能优化到on.就是最小值可以通过贪心的方式从之前三个状态求出来.关键点再于分别维护2,3,5因子这三个队列,再从小到大合并.这种思考量考智商更多,我可以记住这一题,但换一个构造想不出来可能还是得小根堆+哈希.用时差距差不多40ms(150ms->110ms).另,python优先队列比小根堆慢6倍左右.

**标签**:[动态规划],[小根堆],[中等],[掌握]

```cpp
(06_24)
int nthUglyNumber(int n) {
    vector<int> arr(n+2,0);// arr.reserve(n+5);
    int pt_2=0,pt_3=0,pt_5=0;
    int minn;
    arr[0]=1;
    for (int i=2;i<=n;i++){
        minn=min({arr[pt_2]*2,arr[pt_3]*3,arr[pt_5]*5});
        arr[i-1]=(minn);
        if (arr[pt_2]*2==minn) pt_2++;
        if (arr[pt_3]*3==minn) pt_3++;
        if (arr[pt_5]*5==minn) pt_5++;
    }return arr[n-1];
}
```

```python
#小根堆版:
def nthUglyNumber(self, n: int) -> int:
    '''优先队列
    '''
    pq = [1]
    hmap = {1}
    ct=0
    while(pq):
        tmp = heapq.heappop(pq)
        ct+=1
        if ct==n:
            return tmp
        if tmp*2 not in hmap:
            hmap.add(tmp*2)
            heapq.heappush(pq,tmp*2)
        if tmp*3 not in hmap:
            hmap.add(tmp*3)
            heapq.heappush(pq,tmp*3)
        if tmp*5 not in hmap:
            hmap.add(tmp*5)
            heapq.heappush(pq,tmp*5)

#动归版,几乎和小根堆版速度一样
def nthUglyNumber(self, n: int) -> int:
    '''序列合并
    '''
    uglist = [1]
    pt2,pt3,pt5=0,0,0
    while(len(uglist)<n):
        next_num = min(2*uglist[pt2],3*uglist[pt3],5*uglist[pt5])
        uglist.append(next_num)
        if next_num==2*uglist[pt2]:
            pt2+=1
        if next_num==3*uglist[pt3]:
            pt3+=1
        if next_num==5*uglist[pt5]:
            pt5+=1
    return uglist[n-1]
```

**0I60n个骰子的点数**
把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。
你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。

**解析**:一开始想存在数学递推式子,但确定n总结起来很麻烦.不是简单的cn0-cnj这样子,每一个点数是很多组合数的复合.题解里面也没有直接数学做的.还是线性dp(看到n很小其实就是对dp的一个提示了).每个状态由前六个状态得到

**标签**:[动态规划], [线性DP], [中等]

```python
def dicesProbability(self, n: int) -> List[float]:
    '''虽然看着虎人,但无非也还是线性DP,可以从前六个变量中推导当前变量
    '''
    dp = [[0]*(6*n+1) for x in range(n+1)]
    dp[1][1],dp[1][2],dp[1][3],dp[1][4],dp[1][5],dp[1][6]=1,1,1,1,1,1
    for i in range(2,n+1):
        for j in range(i,6*i+1):
            tmp = sum( dp[i-1][ max(j-6,i-1):j ] )
            dp[i][j]=tmp
    total = 6**n
    return [x/total for x in dp[n][n:]]
```

**Im0I13机器人的运动范围**
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

**解析**:遇到有坏点的可达问题我首先想到的就是BFS,这道题有一个隐藏优化是虽然说机器人可以上下左右移动,但其实bfs的话只用右下移动就可以了,因为可达解是三角形扩展的.(但第一次遇到确实不容易想到这个优化)可以优化大约10ms(64ms->56ms),可有可无的优化.

**标签**:[搜索],[广度优先搜索],[容易]

```python
def movingCount(self, m: int, n: int, k: int) -> int:
    '''这哪是DP啊,这不BFS吗!
    广度优先+记忆化
    '''
    from collections import deque
    self.m = m
    self.n = n
    self.k = k
    if k ==0 : return 1
    queue = deque()
    self.map = [[2]*n for x in range(m)] 
    self.map[0][0] = 1 #k=0的情况已经讨论了
    ct=0
    queue.append([0,0])
    while(queue):
        i,j = queue.popleft()
        ct+=1
        # if (self.check(i-1,j)): queue.append([i-1,j])
        if (self.check(i+1,j)): queue.append([i+1,j])
        # if (self.check(i,j-1)): queue.append([i,j-1])
        if (self.check(i,j+1)): queue.append([i,j+1])
    return ct

def check(self,i,j):
    m,n,k = self.m,self.n,self.k
    if i<0 or j<0 or i>m-1 or j>n-1: return False
    if self.map[i][j]==2:
        sumi = sum([int(x)for x in str(i)])
        sumj = sum([int(x)for x in str(j)])
        sums = sumi+sumj
        if sums<=k:
            self.map[i][j]=1
            return True
        else:
            self.map[i][j]=0
            return False
    return False
```

**I0I63(121)股票的最大利润**
假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？

**解析**:严格说是属于序列DP的,但是因为贪心的太明显了,所以很简单可以达到on2->on的优化.维护一个变动当前最小值.

**标签**:[动态规划],[序列DP],[容易]

```python
def maxProfit(self, prices: List[int]) -> int:
    '''简单序列DP
    '''
    maxpro = 0
    n = len(prices)
    if n<=1: return 0
    minbuy=prices[0]
    for i in range(1,n):
        #如果是的那个前最低买入价格,则刷新最低买入价格
        if prices[i]<minbuy:
            minbuy=prices[i]
        else:
        #如果不是最低买入价格,计算profit,刷新最高pro
            if maxpro < prices[i]-minbuy:
                maxpro= prices[i]-minbuy
    return maxpro
```

*优先队列的一些操作命令*

```python
from queue import PriorityQueue
pque = PriorityQueue()
pque.put(-1)
a = pque.get()
```

*最小堆的一些操作命令*

```python
    heap = [1]
    curr = heapq.heappop(heap)
    heapq.heappush(heap, nxt)
```

##### 02_11

**hot416分割等和子集** *(07_05)*
给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

**解析**:可以转化为01背包问题.本来挺难的,但做过一遍之后,有思路,解决方法就比较明确了.

**标签**:[动态规划],[背包问题],[中等]


```cpp
bool canPartition(vector<int>& nums) {
    int sum=0,num;
    for(int elem:nums){sum+=elem;}
    if(sum%2==1){return false;}
    sum/=2;
    int n = nums.size();
    vector<vector<int>> arr(n+5,vector<int>(sum+5,0));
    arr[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++){
            num=nums[i-1];
            if(num>j){arr[i][j]=arr[i-1][j];}
            else{arr[i][j]=max(arr[i-1][j],arr[i-1][j-num]);}
        }
    }
    if(arr[n][sum]==1){return true;}
    else{return false;}
}
```

```python
def canPartition(self, nums: List[int]) -> bool:
    sums = sum(nums)
    # nums.sort()
    if sums%2==1: return False
    tar = int(sums/2)
    n = len(nums)
    dp = [ [0]*(tar+1) for x in range(n+1)]
    dp[0][0]=1
    j_up = 0
    for i in range(1,n+1):
        j_up = min(j_up+nums[i-1],tar)
        for j in range(1,j_up+1):
            dp[i][j] = dp[i-1][j]
            if dp[i][j]==0 and j-nums[i-1]>=0:
                dp[i][j] = dp[i-1][j-nums[i-1]]
        if dp[i][tar]==1: return True #在中间退出可以些许加速
    return False
```

**hot139单词拆分** *2.(02_25 23'27+{0})*
给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。
注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

**解析**:序列DP,有点类似于完全背包问题.挺不好想的.这道题也存在搜索解法,但我记住动归就行了.

**标签**:[动态规划],[序列DP],[偏难]

```python
def wordBreak(self, s: str, wordDict: List[str]) -> bool:
    '''这种分割类型,就是不特定前面哪个可能可以成功,要遍历,一般复杂度都会在n2以上
    这种往往可以用广搜(279)进行加速.但是对于单词这种,就一般只能动归.因为广搜的
    状态转移要对不同的单词进行判断,着非常复杂.还有一个技巧是看数据规模,如果数据规模比较小
    那默认是可以接受n2复杂度的算法.
    '''
    n = len(s)
    hashmp = set(wordDict)
    dp=[0]*(n+1)
    dp[0]=1
    for j in range(1,n+1):
        for i in range(j):
            if s[i:j] in hashmp and dp[i]==1:
                dp[j] = dp[i] #证明了j是前缀
                #避免重复计算
                break
    return dp[n]==1

#广搜解法
def wordBreak(self, s: str, wordDict: List[str]) -> bool:
    from collections import defaultdict,deque
    wordmap = set(wordDict)
    n = len(s)
    jmap = defaultdict(list)
    for i in range(n):
        for j in range(i,n):
            if s[i:j+1] in wordmap:
                jmap[i].append(j+1)

    que = deque([0])
    vis = set()
    while(que):
        idx = que.popleft()
        if idx==n: return True
        if len(jmap[idx])>0:
            for elem in jmap[idx]:
                if elem not in vis:
                    que.append(elem)
                    vis.add(elem)
    return False
```

**hot091解码方法**
一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：
'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。例如，"11106" 可以映射为：
    "AAJF" ，将消息分组为 (1 1 10 6)
    "KJF" ，将消息分组为 (11 10 6)
注意，消息不能分组为  (1 11 06) ，因为 "06" 不能映射为 "F" ，这是由于 "6" 和 "06" 在映射中并不等价。
给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数 。
题目数据保证答案肯定是一个 32 位 的整数。

**解析**:每一个状态都依赖前两个状态,有很多边界条件要考虑清楚.问题不难,但是繁琐.

**标签**:[动态规划],[容易],[烂题]

```python
def numDecodings(self, s: str) -> int:
    '''烂题!
    '''
    n = len(s)
    if '0'==s[0]:return 0 #前导0,为0
    dp = [0]*(n+1)
    if s[-1]=='0':
        dp[1]=0
    else:
        dp[1]=1
    if n==1: return dp[1] #长度为1
    if s[-2] == '0':
        dp[2]=0
    elif int(s[-2:])<=26:
        dp[2]=1+dp[1]
    else:
        dp[2]=dp[1]
    if n==2: return dp[2]
    for i in range(3,n+1):
        if s[-i]=='0': dp[i]=0
        elif int(s[-i:-(i-2)])<=26: 
            dp[i]=dp[i-1]+dp[i-2]
        else:
            dp[i]=dp[i-1]
    return dp[n]
```

**hot279 完全平方数** *2.(02_25 45'+{3})* *3.(03_20 9'09+{0})*
给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

**解析**:(03_20)完全掌握了,记忆化,bfs考的挺全面的.
(02_25)有重新经历了一遍想这道题的过程,先写的动归解,发现用时好高,后来想dfs写道一半发现应该bfs,提交,发现空间复杂度边高了,加上记忆化.相当于一道题写了三遍.花了45'.
这道题,动归最容易想,但是广搜+记忆化是最优解.

**标签**:[广度优先搜索],[偏难]

```python
def numSquares(self, n: int) -> int:
    '''这个和132很相似,都是从不特定的前序状态进行规划
    但这题用动归要比bfs跨的时间长得多
    这道题要再刷,这道题用广搜而不是深搜的原因再于,在最早遇到结束的那层程序就可以结束了,
    但深搜要遍历所有的结果,这就大大浪费了时间!
    广搜节省了时间,但是如果没有记忆化的话还是会浪费很多空间.
    这道题想用动归解出来很容易,但是想到广搜+记忆化不容易,值的二刷.
    同理,132是不是也能用这个方法解出来阿?
    '''
    from collections import deque
    queue = deque([[n,0]])
    visited = set()
    while(queue):
        n,layer = queue.popleft()
        sn = int(n**(1/2))
        if sn**2==n: return layer+1 #遇到完全平方数,搜索结束
        for i in range(sn,0,-1): #sn,...,1
            tmp = n-i**2
            if tmp not in visited:
                visited.add(tmp)
                queue.append([tmp,layer+1])
            else:
                continue
```

##### 02_10

今天做几道回文串的题吧.

**0II94(132)最少回文分割** *2.(02_25 35'+{0}+{5})* *3.(03_02 19'40+{0})*
给定一个字符串 `s`，请将 `s` 分割成一些子串，使每个子串都是回文串。
返回符合要求的 **最少分割次数** 。

**解析**: *(03_02)*三刷这个题就思考的很清楚了,分成两阶段,第一阶段N2预处理得到所有回文串的位置.第二阶段N2动态规划得到每一段字符串的最小回文次数.状态转移方程:如果i-j有回文,则dp[j]=min(dp[j],dp[i-1]+1). 下标本身就是有麻烦,要么初始化一下从2开始,要么从1开始但设置一个0的伪值.
*(02_25)*对回文类问题请考虑n2复杂度的方法!这道题间子串表和动态规划都是O(n2)的复杂度!
首先这个问题是建立在 `<hot647>`基础上的,也就是说需要先遍历找到所有的回文子串的位置,然后把问题看成类似背包问题.j的状态由j前面所有回文的最小值确定.这个状态转移方程是比较难想到的.

**标签**: [动态规划],[偏难]

```python
def minCut(self, s: str) -> int:
    '''这居然是个背包问题的动态规划即使第二次做,而且做了很多回文分割的题之后
    我还是大为震惊.
    最后使用动归的背包问题求解,装j的时候考虑之前的最好价值+1,反正听抽象
    速度比之前快纯粹快来了递推求回文串表,但是代价是大麻烦了导致写错,而且
    下面的动归也太草率了,动归需要提前把转移方程想清楚再开始敲
    '''
    #step1 制作回文字串查找表
    n = len(s)
    find = [[0]*n for i in range(n)] #n*n列表储存回文子串
    for i in range(n):
        ti,tj = i,i
        while(s[ti]==s[tj]):
            find[ti][tj] = 1
            ti,tj=ti-1,tj+1
            if ti<0 or tj>=n: break
        if i<n-1:
            ti,tj = i,i+1
            while(s[ti]==s[tj]):
                find[ti][tj]=1
                ti,tj = ti-1,tj+1
                if ti<0 or tj>=n: break

    #step2 动态规划dp[i]=min(dp[i],dp[j]+1 (find[j+1][i]==1) )
    dp = [float('inf')]*(n+1)
    dp[0]=0
    dp[1]=1 #初始化
    for j in range(2,n+1):
        #i的范围可以到j
        for i in range(1,j+1):
            if find[i-1][j-1]==1: 
                dp[j] = min(dp[j],dp[i-1]+1)
    return dp[n]-1
```

**II018(125)有效回文**
给定一个字符串 `s` ，验证 `s` 是否是 **回文串** ，只考虑字母和数字字符，可以忽略字母的大小写。
本题中，将空字符串定义为有效的 **回文串** 。

**解析**:使用lower()和isalnum()会让代码更简洁,但是感觉有点投机取巧?双指针是肯定要的.其实就算不用那两个函数也是自己造这个轮子罢了.

**标签** [容易],[链表]

```python
def isPalindrome(self, s: str) -> bool:
    '''就是双指针,怎么判断字符都可以吧
    用isalnum会省去很多判断的问题
    lowder由会省去一些判断
    当然这些轮子也可以很简单的实现
    '''
    s = ''.join([x.lower() for x in s if x.isalnum() ])
    # print(s)
    i ,j = 0,len(s)-1
    while (i<j):
        if s[i]!=s[j]: return False
        i+=1
        j-=1
    return True
```

**hot647回文子串** (02_10); (07_04 {8'}+{0}+{0})
给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。
回文字符串 是正着读和倒过来读一样的字符串。
子字符串 是字符串中的由连续字符组成的一个序列。
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

**解析**:和005一样,只是要用ct记录正确回文的个数,递推要比递归更省时间,但是递归代码更简洁.

**标签**:[动态规划],[一维动归],[递推],[中等],[掌握]

```python
def countSubstrings(self, s: str) -> int:
    '''这不是和第五题一模一样吗,刷了这道题就相当于第五题三刷了.
    递归会比递推慢一些,但以后同样的思路,具体实现我还是会选择递归
    0.时间上的增加不是数量级层面的,如果面试的时候没有明确要求,说明只要
    思路对了肯定时能把题写出来的
    1.题归更能体现计算机变成的思想
    2.题归相当于系统帮你维护栈,写其代码来必然会简洁一些
    '''
    ct = 0
    n = len(s)
    for i in range(n):
        ti,tj = i,i
        while(s[ti]==s[tj]):
            ct+=1
            ti-=1
            tj+=1
            if ti<0 or tj>=n: break
        if i<(n-1):
            ti,tj = i,i+1
            while(s[ti]==s[tj]):
                ct+=1
                ti-=1
                tj+=1
                if ti<0 or tj>=n: break
    return ct
```

hot234回文链表
给你一个单链表的头节点 `head` ，请你判断该链表是否为回文链表。如果是，返回 `true` ；否则，返回 `false` 。

**解析**:快慢指针是一定的.最容易思路:slow经过的时候增加一个prev变量,然后slow和fast从新过一遍.但这样会多占空间,因为建立新变量也会消耗一些时间(大概多2·00ms).另一种就是slow沿路更改next变成prev,但这种比较麻烦的是要用额外变量取记(就像修改链表一样).到重点之后,根据奇偶性不同还要分别讨论.比较麻烦,笔试的时候如果不考虑时间复杂度还是优先添加一个prev吧.

**标签**:[快慢指针],[链表],[简单]

```python
def isPalindrome(self, head: Optional[ListNode]) -> bool:
    '''快慢指针找中点,好像如果修改slow.next而不是增加一个prev属性可以更快
    (可以理解,应该和内存操作)有关系,但我这样也还好了
    如果修改next要增加两个变量,并且fast和slow迭代顺序也变化了,变得麻烦,最后通过的就是麻烦的版本了
    '''
    slow,fast,preview = head,head,None
    while (fast.next and fast.next.next):
        fast = fast.next.next
        tmp = slow.next
        slow.next = preview
        preview = slow
        slow = tmp
    #前面找一半不用改变,就是后面在怎么处理要修改   

    right = slow.next
    if not fast.next:#奇数
        left = preview
    else:
        slow.next = preview
        left = slow

    while(left and right):
        if left.val != right.val:
            return False
        left = left.next
        right = right.next
    return True
```

##### 02_09

动态规划四道题:

- [X] hot5
- [X] hot22
- [X] hot53
- [X] hot62

**hot005最长回文子串**
给你一个字符串 s，找到 s 中最长的回文子串。
如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。

**解析**:(03_02):中心展开,遍历字符串中所有前在的回文串.
这是一个从动归出发,但最后优化成递推的题目.或许也可以一开始直接想到递推?动归的角度就是找到下一个状态只对角线元素.
但递推的想法是,如果当前步不是回文,则下一步必不是回文.因此不需要遍历所有的动归状态,可以大幅减枝.除此之外,搜索内容的时候while循环要比dfs快,如果用递推的化,只需要依次搜索初始状态,不需要用dp数组记录接空间.优化之前5000ms优化之后只需340ms,这道题优化不优化区别比较大.整体题目也比算较复杂.

**标签**:[递推],[一维动归],[偏难]

```python
def longestPalindrome(self, s: str) -> str:
    '''这是一道比较复杂的动归题了,状态方程不好列,并且遍历方式也不是传统的
    循环,而是三角形遍历.基本算是我目前能做出来的动归题考上限的的了.
    而且这道题在三角形遍历基础上还有进一步减枝的优化,因为前一部如果不是回文串,
    下一步也必不是回文串,这样可以避免很多无效判定
    再进一步dp也可以不要,因为每一项都是独立的递推
    '''
    n = len(s)
    # dp = [[0]*n for x in range(n)]
    reti,retj=0,0
    for i in range(n):
        # dp[i][i]=1 #i,j相等的情况
        ti,tj = dfs(i-1,i+1,s)
        if (tj-ti>retj-reti):
            reti,retj = ti,tj
        if i<n-1 and s[i]==s[i+1]: #j-i=1的情况
            ti,tj = dfs(i-1,i+2,s)
            if (tj-ti>retj-reti):
                reti,retj = ti,tj

    return s[reti:retj+1]

def dfs(i,j,s):
n = len(s)
while not( i<0 or j >=n or s[i]!=s[j]):
    i-=1
    j+=1
return i+1,j-1
```

hot022括号生成 *3.(03_31) 7'02+{0}*
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

**解析**:这是一个比较标准的搜索问题,并且减枝处理也是理所当然的(如果当前括号方式不可能得到正确答案,则不再往下搜索)

**标签**:[搜索],[dfs],[偏易]

```python
def generateParenthesis(self, n: int) -> List[str]:
    '''这种题哪里动归了啊?
    我看就是个搜索问题,一个标准递归问题
    如何返回,状态如何转移,都很标准.题目难度是要想清楚')'数<')'数是判断
    能否添加')'的充要条件
    '''
    ans = []#定义一个全局变量,储存答案
    def dfs(cur, n, state):
        left,right = state
        if left==n and right==n: 
            ans.append(cur)
            return 
        if left<n:
            dfs(cur+'(',n,[left+1,right])
        if right<left:
            dfs(cur+')',n,[left,right+1])

    dfs('(',n,[1,0])
    return ans
```

**hot053最大子数组和**  *2.(02_27 19'00)*
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
子数组 是数组中的一个连续部分。

**解析**:还可有前缀和解法,代码长度和时间复杂度和动归完全一致.而且我觉得这题用动归其实更合适一点.
与其说动归,我更愿意称之为递推,因为不需要转移方程,只需要前一个状态就能推出下一个状态.但状态定义是比较有动归的味道,可以说递推是优化了之后的动归吧(因为不是很好想).状态定义是考虑当前元素的最大和.注意:**max操作要比if判断操作耗时长整整1倍**.

**标签**:[动态规划],[一维动归],[递推],[容易]

```python
def maxSubArray(self, nums: List[int]) -> int:
    '''这种感觉也不是标准动归把,充其量是一个递推,一维动归?
    而且我知道这个可以优化到只需要o(1)的空间,因为实际上只需要前一个元素的状态就可以了
    一个很怪异的现象是,max操作要比if判断操作耗时长整整1倍
    '''
    max_v = nums[0]
    prev_v = nums[0]
    for i in range(1,len(nums)):
        #要么就取当前元素,要么取上一个元素+当前元素
        prev_v = nums[i] if prev_v<=0 else prev_v+nums[i]
        max_v = max_v if prev_v<max_v else prev_v
    return max_v

#前缀和解法
def maxSubArray(self, nums: List[int]) -> int:
    '''看到连续数组,很可能就和滑动窗口或者前缀和有关系19'00
    这次是看到了存在o(n)的解法,但也不能算偷看,因为毕竟就在题目描述下面
    还可以从动归角度理解,dp[i]为含有i的最大子数组.
    '''
    min_pre = 0
    ans = float('-inf')
    cur_pre=0
    for num in nums:
        cur_pre+=num
        if cur_pre-min_pre>ans: ans=cur_pre-min_pre
        if min_pre>cur_pre: min_pre=cur_pre
    return ans
```

**hot062不同路径**
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
问总共有多少条不同的路径？

**解析**:最基础的路径规划问题,处理好边界条件没有错的可能性复杂度O(m*n)
**标签**:[动态规划],[容易]

```python
def uniquePaths(self, m: int, n: int) -> int:
    '''这是最标准的路径规划问题了,也是我高中第一次接触动态规划学的题
    还是很怀念
    '''
    dp = [[0]*n for i in range(m)]
    for i in range(m):
        dp[i][0]=1
    for j in range(n):
        dp[0][j]=1
    for i in range(1,m):
        for j in range(1,n):
            dp[i][j] = dp[i-1][j]+dp[i][j-1]
    return dp[m-1][n-1]
```

```cpp
//第一个cpp解题的代码
int uniquePaths(int m, int n) {
    int map[(m+1)][(n+1)];
    memset(map,0,sizeof(map));
    map[1][1]=1;
    for (int i=1;i<=m;i++){
        for (int j=1;j<=n;j++){
            if(i==1 && j==1){continue;}
            map[i][j]=map[i-1][j]+map[i][j-1];
        }
    }
    return map[m][n];
}
```

##### 02_07

**hot034在排序数组中查找元素的第一个和最后一个位置**

给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]。
你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

**解析**做的比较愉快的一个题,考察了二分的基本功.就是边界条件有很多需要判断,比如target在数组外,target不在数组内,数组为空等等.**心得**:对于我这种写法,在数组里的情况时,数组一定不能为空(要提前判断),因为右端点就要定义成数组长度,而且最低返回的也是第0元素.**感受**对于数组的二分题,二分部分不会特的难,因为 ``l=mid+1``的判断条件不是连续的,比较好判断.

**标签**:[二分查找],[中等]

```python
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        if len(nums)==0: return [-1,-1] #空数组直接返回-1-1
        if target> nums[-1] or target<nums[0]: return [-1,-1] #不在数组内的情况
        st = erfen(nums,target-0.5)
        if nums[st]!=target: return [-1,-1] #组内找不到
        ##额外考虑target是右边界的情况
        ed = erfen(nums,target+0.5)-1 if target<nums[-1] else len(nums)-1
        return [st,ed]
def erfen(nums,tar):
    l,r = 0,len(nums)-1
    while(l<r):
        mid = (l+r)//2
        if tar>nums[mid]:
            l = mid+1
        else:
            r = mid
    return l
```

**II0II72求平方根**

评价:第三遍做还是错了,对于这种基本框架的理解有两个难点,本题只涉及其中一个.就是第8行,什么时候 ``l=mid+1``;第三遍我仍然写的是mid\*\*2\<x;
判断再于,l=mid+1是最后的导出判断,对于这种涵盖正确答案的,对于**l=mid+1的判断不能有正确情况在这里面**,同时有要包含所有的left右移动的情况.如果mid\*\*2\< x,因为题目要求是向下取整,所有存在正确的情况涵盖在里面,只有(mid+1)\*\*2包含了所有错误情况.另一端就不用判断了,直接else就行.这是这种二分的第一个难点.
第二个难点在于:有的时候满足题意的不在题目中,最后会返回一个插入位置.比如那种把x插入一个有序数组的题,对于l=mid+1的输出结果,是求**前插**而不是后插,也就是返回的位置,就是要插入的序号.(比如返回0就代表要插入当前数组的第0位置).此时,应该事先思考会不会插到最后一位的后面(前插插不到最后,如果会的话要单独判断).

```python
class Solution:
    def mySqrt(self, x: int) -> int:
        if x==0: return 0
        if x==1: return 1
        l,r = 1,x//2
        while(l<r):
            mid = (l+r)//2
            if (mid+1)**2<=x:
                l=mid+1
            else:   
                r=mid
        return l
```

**hot 287寻找重复数**
给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。
假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。
你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。

**解析**: 这道题运行最快O(n)(代码也是最简洁)的做法是快慢指针,最好想到的方法是二分查找o(nlogn)(**也有点难**),二分查找:要想到小于数组的数字个数对于重复数字左边和右边有区别(左边比序号小,右边比序号大).我选择了快慢指针的方式.这个其实数学证明要花很多功夫.结论:1.当一个链表中有环,则通过快慢指针的方式可以找到入环点. 2.本题可以抽象成一个起始点没有入度的n点n边的链表,则起始点做再的连同链表中比存在可以代表重复数的环.(而不存在1-2-0这样的无重复数环),关键就在于这样的环所有点都有入度,而起始点没有入度,所有点都有出度,所有起始点所在链表必然存在两个入度的环(重复数字)

**标签:**[二分],[搜索]

```python
def findDuplicate(self, nums: List[int]) -> int:
    n = len(nums)
    left, right = 0, n
    while left < right:
        mid = (left + right) // 2
        cnt = sum(num <= mid for num in nums)   # nums中 <=mid 的元素个数
        if cnt <= mid:      # 目标元素在mid右侧
            left = mid+1
        else:
            right = mid
    return left
```

**hot 240搜索二维矩阵 II**
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：
    每行的元素从左到右升序排列。
    每列的元素从上到下升序排列。

**解析:**这道题二分的复杂度是O(log(max(m,n)*min(m,n))),搜索的复杂度是O(max(m,n)),如果mn差距不大的化,搜索应该更快,如果差距很大那么二分其实会快一些.我只用了搜索解决,算是一种巧办法吧.总右上角搜索,正确性再于每次消除的一行一定是不含正确答案的,所以最后走完要么能遇到,要么就是不再矩阵内.
**标签:**[二分][搜索]

```python
def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
    '''这道题虽然标签写了二分,但实际上可以通过max(m,n)的复杂度搜索出来,从左上角开始
    每一次判断都可以消除一行的可能性,根本不需要mlog(n)的遍历

    m,n,i,j要分清楚
    '''
    m,n = len(matrix)-1,len(matrix[0])-1
    i,j = 0,n
    while(i<=m and j>=0):#如果在矩阵内部
        cur = matrix[i][j]
        if cur==target: return True
        elif cur < target: i+=1
        elif cur > target: j-=1
    return False
```

**0II68(035)查找插入位置**
给定一个排序的整数数组 nums 和一个整数目标值 target ，请在数组中找到 target ，并返回其下标。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为 O(log n) 的算法。

**解析**:就是标准二分查找公式,应该放在二分查找部分的最前面

**标签:**[二分查找],[偏易]

```python
def searchInsert(self, nums: List[int], target: int) -> int:
    '''标准的二分查找公式
    '''
    if target>nums[-1]:
    returnlen(nums) #否则插在最后一位
        left,right = 0,len(nums)-1
    while(left<right):
            mid = (left+right)//2
    if nums[mid]<target:
                left = mid+1
    else:
                right = mid
    return left

```


**hot033搜索旋转排序数组** *2.(02_28) 30'23+{0}* *3.(03_21) 24'11+{1}*

整数数组 nums 按升序排列，数组中的值 互不相同 。
在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

**解析**:(03_21)做的比以前更快,但是2个乱序写在了一起,没有分清楚.所以错了一次.
(02_28)之前总是把乱序和顺序放在一起讨论,这样总是要考虑如多另一方是乱序,如果另一方是顺序要怎么处理.其实分三种情况的话会好想很多,2个乱序+1个顺序.每种情况分别进行二分.以后这道题就以这种思路做解.
第一遍不了解二分基本框架所以很麻烦,第二遍做的时候代码简单了很多.**关键点1**:可以通过mid和左右端点的判断来找到哪边是顺序的,哪边是乱需的(不需要先找点再二分,而可以直接用一次二分就确定为值)**关键点2**:要考虑到不旋转(以0为轴)和整体都旋转的边界条件,和平凡结果的处理方式是不同的.

**标签**:[二分查找],[偏难],[掌握]

```python
#这样写更不爱出错,分三种情况:
def search(self, nums: List[int], target: int) -> int:
    n = len(nums)
    left,right = 0,n-1
    tar = target
    while(left<right):
        mid = (left+right)//2
        if nums[mid]>=nums[left] and nums[left]>nums[right]:
            if tar>nums[mid] or tar<nums[left]:
                left = mid+1
            else:
                right = mid
        elif nums[mid]<nums[left] and nums[mid]<nums[right]:
            if tar>nums[mid] and tar<=nums[right]:
                left = mid+1
            else:
                right=mid
        elif nums[mid]>=nums[left] and nums[mid]<nums[right]:
            if tar>nums[mid]:
                left=mid+1
            else:
                right =mid
    if nums[left]==tar: return left 
    else: return -1

#这样思考量更大一些
    def search(self, nums: List[int], target: int) -> int:
        n = len(nums)
        if n==0: return -1
        l,r=0,n-1
        while(l<r):
            mid = (l+r)//2
            if nums[r]>nums[mid]: #右升序
                if target>nums[mid] and target<(nums[r]+0.01): #<=>x在mid右边
                    l = mid+1
                else:
                    r = mid
            else: #左升序
                if target>nums[mid] or target<nums[l]: #<=>x在mid右边
                    l = mid+1
                else:
                    r = mid
        if nums[l]==target:
            return l
        else:
            return -1
```

**hot300最长递增子序列**
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

**评价**:难点在**贪心**.这道题虽然nlogn的解答是贪心+二分查找,而且看不到动态规划的影子,但其实普通人一开始想都会想到n2的动归解法,遍历前面的子序列,符合条件的+1.破解之处是贪心,只要维护一个最优子序列,就可以了.

**标签** [贪心],[偏难]

```python
class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        tail = []
        n = len(nums)
        dp = [0]*n
        for i in range(n):
            #查找第i个数字在理想子序列中的为值
            #序列为空,或者单调增,后插即可
            if not tail or nums[i]>tail[len(tail)-1]:
                tail.append(nums[i])
            #否则,要替换前面的值
            else:#排除了后插情况,可以放心前插 
                #这里比较巧妙就是每个位置是当前长度序列的最小情况,但并不是连续情况
                pos = find_pos(tail,nums[i])
                tail[pos] = nums[i]
        return len(tail)

def find_pos(nums,tar):
    l,r = 0,len(nums)-1
    while (l<r):
        mid = (l+r)//2
        if nums[mid]<tar:
            l = mid+1
        else:
            r = mid
    return l
```

**hot004寻找两个正序数组的中位数[不值的做]**

给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
算法的时间复杂度应该为 O(log (m+n)) 。

**解析**:虽然题目考到了二分的本质应用,但如果面试能出这么难的我也认了.本质就是利用两个数组都排好序这一点,每次去掉一半不符合要求的.但是1.奇偶性要进行判断2.时刻要考虑某一个列表被排除完了怎么判断.有很多很多边界情况要考虑,不然就不符合要求.

**标签**:[烂题]

```python
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        '''这道题某种程度上揭示了二分的本质:每次想办法去除一半的错误答案
        用迭代法可以覆盖其他情况而不仅仅针对中位数情况
        但是要考虑很多边界条件
        '''
        m,n = len(nums1),len(nums2)
        if m==0 and n==0: return -1
        if m>n:
            #强制nums1是较小的
            m,n=n,m
            nums1,nums2 = nums2,nums1
        if m==0: 
            if n%2==1:
                return nums2[n//2]
            else:
                return (nums2[n//2]+nums2[n//2-1])/2

        #求一个mid返回四个值,根据奇数偶数分别讨论
        mid = (m+n+1)//2 #奇数返回中间,偶数返回中间靠前
        nums1_r,nums2_r = dfs(nums1,nums2,mid)
        print(nums1_r,nums2_r)
        if (m+n)%2==0: return (nums1_r+nums2_r)/2
        else: return nums1_r


def dfs(nums1,nums2,mid):
    while(mid!=1 ):
        l1 = min(mid//2-1,len(nums1)-1)
        l2 = mid-(l1+1)-1
        if nums1[l1] <= nums2[l2]:
            nums1 = nums1[l1+1:]
            mid-=(l1+1)
        else:
            nums2 = nums2[l2+1:]
            mid-=(l2+1)
        if not nums1:
            if len(nums2)>1:
                return [nums2[l2],nums2[l2+1]]
            else:
                return [nums2[l2],nums2[l2]]
        if not nums2:
            if len(nums1)>1:
                return [nums1[l1],nums1[l1+1]]
            else:
                return [nums1[l1],nums1[l1]]

    middle = min(nums1[0],nums2[0])
    middle_p = max(nums1[0],nums2[0])
    if len(nums1)>1:
        middle_p = min(nums1[1],middle_p)
    if len(nums2)>1:
        middle_p = min(nums2[1],middle_p)
    return [middle,middle_p]
```


**hot011 盛最多水的容器**

给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。

评价:难点在贪心,参考答案说的好,移动长的边一定会变小,移动短的边有可能变大,所以最大的面积一定是通过不断移动较短边得到的.

```python
class Solution:
    def maxArea(self, height: List[int]) -> int:
        left,right=0,len(height)-1
        max_con = 0 
        while (left<right):
            max_con = max(min(height[left],height[right])*(right-left),max_con)
            if height[left]<height[right]:
                left+=1
            else:
                right-=1
        return max_con
```

**hot055 跳跃游戏**

给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个下标。

评价:贪心贪的是最大步数,每次可以直接刷新,难度不大
[贪心][简单动态规划]

```python
class Solution:
    def canJump(self, nums: List[int]) -> bool:
        n = len(nums)
        max_len = 0 #能到达的下标
        for i in range(n):
            if i>max_len: return False #达不到这一部
            else:
                max_len = max(max_len,i+nums[i])
                if max_len>=n-1:#如果能到达,返回
                    return True
  
```

**hot406根据身高重建队列**

**题干:** 假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。
请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。

**解析:** 这道题不好想到要用贪心,贪在哪里呢?*贪心其实就是看似有很多中可能,但其实想达到最后的最优接只能中间每一步也走一个确定的路线,从而把n^2复杂的问题转成n*这题先排高个子,这样不论后面矮个字怎么排,都不会影响高个子的正确性.而同样的高个子,按照前面人少到多排可以减少insert增加append.

```python
def reconstructQueue(self, people: List[List[int]]) -> List[List[int]]:
    #先排高个子再排矮个子,因为矮个子怎么排也不会影响k,也就是说只要高个子站定了,正确性不会被打破,如果先排矮个字则没有这个福利
    people.sort(key=lambda x: (-x[0],x[1]))
    ans = []
    for person in people:
        if len(ans)>person[1]:
            #左:插入的位置,右:插入的元素
            ans.insert(person[1],person)
        else:
            ans.append(person)
    return ans
```

##### 快慢指针

**hot141环形链表**

给你一个链表的头节点 head ，判断链表中是否有环。
如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。
如果链表中存在环 ，则返回 true 。 否则，返回 false 。

**解析**:做了287之后这个题就很简单了,因为这是287的一个子问题.判断链表是否有环.快慢指针如果相遇就有环,如果快指针能走到终点就没有环.

```python
def hasCycle(self, head: Optional[ListNode]) -> bool:
    '''做了142再做141就没什么了,还是双指针,如果能相遇就是有环,否则无环
    边界就是空数组要判断一下
    '''
    #空链表,没有第二\第三元,全返回false
    if not head or not head.next or not head.next.next: 
        return False
    slow,fast = head.next,head.next.next
    while(slow!=fast):
        if (not fast.next or not fast.next.next):
            return False
        else:
            slow = slow.next
            fast = fast.next.next
    return True
```

**hot142环形链表 II** *2.(04_11) 31'27+{0} CPP*

给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
不允许修改 链表。

**解析:**:是141的进阶,但仍然比较简单.这次需要的是返回环的为值,通过相遇后重置慢指针,之后快慢指针都自增1即可.注意重置之后先判断再走,考虑了起点就是环的情况.(03_07)对于快慢指针在环中一定会相遇,可以理解为一个追击问题.

**标签:**[链表],[环],[中等]

```python
def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
    '''采用快慢指针的方式
    快慢指针构造有以下几点要注意:(实际模拟一下就可以写出来)
    1.快,慢指针的起点都是原点来找环.
    1.5一开始先走再判断,不然没意义
    2.相遇之后,重置之后,先判断再走,这样可以满足如果环在起点的情况
    '''
    #空链表情况
    if not head: return None
    slow,fast = head,head
    cir=False
    while(fast.next and fast.next.next):
        slow = slow.next
        fast = fast.next.next
        if fast == slow:
            cir = True
            slow = head
            break
    if cir==False: return None #无环,返回none
  
    while(fast!=slow):
        fast = fast.next
        slow = slow.next
    return fast
```

```CPP
#define LN ListNode
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        LN *fast,*slow;
        fast = slow = head;
        if (not head){return fast;}
        while(fast->next and fast->next->next){
            slow = slow->next;
            fast = fast->next->next;
            if (slow==fast){
                slow=head;
                while(1){
                    if(slow==fast) return fast;
                    slow  = slow->next;
                    fast = fast->next;
                }
            }
        }return nullptr;
    }
};
```

---

---

---

---

---

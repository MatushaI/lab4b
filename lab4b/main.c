
#include <stdio.h>
#include "splayTree.h"
#include <stdlib.h>
#include "dialog.h"
#include "getFunctions.h"

int main(int argc, const char * argv[]) {
   
    Tree *tree = treeBinaryCreate();
    Node *search = calloc(1, sizeof(Node));
    
    const char *msgs[] = {"0. Выход", "1. Добавить элемент", "2. Поиск", "3. Удаление", "4. Печать дерева", "5. Обход дерева в обратном порядке", "6. Импорт из файла"};
    const int Nmsgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*func[])(Tree *, Node **) = {NULL, addInfo_In, search_In, delete_In, printTable_In, walkTree_In, importFile};
    
    int rc;
    while((rc = dialog(msgs, Nmsgs, NULL))){
        if(!func[rc](tree, &search)){
            break;
        }
    }
    free(search);
    deleteBinaryTree(tree);
    return 0;
    
    return 0;
}

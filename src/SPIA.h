#ifndef SPIA_H
#define SPIA_H

#include <stdlib.h>
#include <stdio.h>

//WHOLE THING IS AN ECS, THIS IS TO MINIMIZE COMPLEXITY FOR THE USER OF THE API

typedef struct PHYSICSOBJ_STRUCT {  
  float x;
	float y;
	float w;
	float h;
	bool colR;
	bool colL;
	bool colT;
	bool colB;
	int type; //0 is rectangle, 1 triangle, 2 circle (So far) 
}PhysicsObj;

// BINARY TREE CODE
typedef struct BTNODE_STRUCT {
				int id;
        PhysicsObj val;
				struct BTNODE_STRUCT * left;
				struct BTNODE_STRUCT* right;
}BTNode;

typedef struct BTREE_STRUCT {
				BTNode* root;
				int tmp;
				int length;
}BTree;

void bnAddN(BTree* p_t, BTNode* p_this, BTNode* p_n){
				if(p_n->id < p_this->id) {
								if(p_this->left == NULL){
												p_t->length++;
												p_this->left = p_n;
								} else {
												bnAddN(p_t, p_this->left, p_n);
								}
				} else if(p_n->id > p_this->id){
								if(p_this->right == NULL){
												p_t->length++;
												p_this->right = p_n;
								} else {
												bnAddN(p_t, p_this->right, p_n);
								}
				}
}

BTNode* cBTNode(int p_id) {
				BTNode* n = malloc(sizeof(struct BTNODE_STRUCT));
				n->left = NULL;
				n->right = NULL;
        n->id = p_id;
				n->val = NULL;
				return n;
}

BTree* cBTree() {
				BTree* t = malloc(sizeof(struct BTREE_STRUCT));
				t->root = NULL;
				t->tmp = 0;
				t->length = 0;
				return t;
}

BTNode* btAddN(BTree* p_t, int p_id){
				BTNode* n = cBTNode(p_id);
				if(p_t->root == NULL){
								p_t->length++;
								p_t->root = n;
				} else {
								bnAddN(p_t, p_t->root, n);
				}
				return n;
}

void bTNVisit(BTNode* p_n, BTree* p_t){
				if(p_n->left != NULL)
								bTNVisit(p_n->left, p_t);
				printf("%d \n", p_n->id);
				if(p_n->right != NULL)
								bTNVisit(p_n->right, p_t);
}

BTNode* bTNSearch(BTNode* p_n, int p_val){
				if(p_n->id == p_val){
								return p_n;
				} else if(p_val < p_n->id && p_n->left != NULL){
								bTNSearch(p_n->left, p_val);
				} else if(p_val > p_n->id && p_n->right != NULL){
								bTNSearch(p_n->right, p_val);
				}
}

void bTSort(BTree* p_t){
				bTNVisit(p_t->root, p_t);
}

BTNode* bTSearch(BTree* p_t, int p_val){
				BTNode* n = bTNSearch(p_t->root, p_val);
				return n;
}

void bTNFree(BTNode* p_n){
				if(p_n->left != NULL){
								bTNFree(p_n->left);
				} else if(p_n-> right != NULL){
								bTNFree(p_n->right);
				} else {
								free(p_n);
				}
}

void bTFree(BTree* p_t){
	if(p_t->root != NULL){
		bTNFree(p_t->root);
	} else {
		free(p_t);
	}
}

typedef struct SPIA_STRUCT  {
	//PhysicsObj physicsObjs[100]; //TEMPORARY WILL BE ADDING A DYNAMIC BINARY TREE IN THE NEAR FUTURE
	BTree* physicsObjs = cBTree();
}SPIA;

int newPhysicsObj(SPIA* s, float p_x, float p_y, float p_w, float p_h, int p_type){
	int id = s->physicsObjs->length;
	
	BTNode* n = btAddN(s->physicsObjs, id);
	n->val.x = p_x;
	n->val.y = p_y;
	n->val.w = p_w;
	n->val.h = p_h;
	n->val.type = p_type;
	n->val.colL = false;
	n->val.colR = false;
	n->val.colT = false;
	n->val.colB = false;
	
	return id;
}

void updatePos(SPIA* s, float p_x, float p_y, float p_w, float p_h){
  for(int i = 0; i < s->physicsObjs->length + 1; i++){
    BTNode* n = bTSearch(s->physicsObj, i);
		n->val.x = p_x;
		n->val.y = p_y;
		n->val.w = p_w;
		n->val.h = p_h;
	}
}

void updateCol(SPIA* s){
  //PhysicObj o[100] = s->physicsObjs;
  //int totalO = s->totalPhysicsObjects; 

  for(int i=0; i < s->physicsObjects->length + 1; i++){
    for(int j=0; j < s->physicsObjs->length + 1; j++){
      BTNode* foundp = bTSearch(s->physicsObjs, i);
			BTNode* foundo = bTSearch(s->physicsObjs, j);

			switch(foundp->val.type){
        case 0:
          switch(foundo->val.type){
            case 0:
              //RECT RECT CHECKS
              if(foundp->val.x + foundp->val.w >= foundo->val.x && foundp->val.y >= foundo->val.y - foundp->val.h && foundp->val.y <= foundo->val.y + foundo->val.h){
              	foundp->val.colR = true;
                foundo->val.colL = true;
               } else {
                foundp->val.colR = false;
                foundo->val.colL = false;
               }
               if(foundp->val.x <= foundo->val.x + foundo->val.w && foundp->val.y >= foundo->val.y - foundo->val.h && foundp->val.y <= foundo->val.y + foundo->val.h){
                foundp->val.colL = true;
                foundo->val.colR = true;
               } else {
                foundp->val.colL = false;
                foundo->val.colR = false;
               }
               if(foundp->val.y + foundp->val.h <= foundo->val.y && foundp->val.x >= foundo->val.x - foundp->val.w && foundp->val.y <= foundo->val.y + foundo->val.h){
                foundp->val.colB = true;
                foundo->val.colT = true;
               } else {
                foundp->val.colB = false;
                foundo->val.colT = false;
               }
               if(foundp->val.y <= foundo->val.y + foundo->val.h && foundp->val.x >= foundp->val.x - foundo->val.w && foundp->val.x <= foundo->val.x + foundo->val.w){
                foundp->val.colT = true;
                foundo->val.colB = true;
               } else {
                foundp->val.colT = false;
                foundo->val.colB = false;
               }
					
              break;
              case 1:
                //RECT TRI CHECKS
              break;
              case 2:
                //RECT CIRC CHECKS
              break;
					}
        break;
        case 1:
          switch(foundo->val.type){
            case 0:
              //TRI RECT CHECKS
            break;
            case 1:
              //TRI TRI CHECKS
            break;
            case 2:
              //TRI CIRC CHECKS
            break;
          }
        break;
        case 2:
          switch(foundo->val.type){
            case 0:
              //CIRC RECT CHECKS
            break;
            case 1:
              //CIRC TRI CHECKS
            break;
            case 2:
              //CIRC CIRC CHECKS
            break;
          }
       break;
    }
	}
 }
}

void updateSPIA(SPIA* s, float p_x, float p_y, float p_w, float p_h){
  updatePos(s, p_x, p_y, p_w, p_h);
  updateCol(s);
};

void freeSpia(SPIA* s){
	if(s->physicsObjs != NULL){
		bTFree(s->physicsObjs);
	} else {
		free(s);
	}
}

#endif

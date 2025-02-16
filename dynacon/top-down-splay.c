/*
                An implementation of top-down splaying
                    D. Sleator <sleator@cs.cmu.edu>
    	                     March 1992

  "Splay trees", or "self-adjusting search trees" are a simple and
  efficient data structure for storing an ordered set.  The data
  structure consists of a binary tree, without parent pointers, and no
  additional fields.  It allows searching, insertion, deletion,
  deletemin, deletemax, splitting, joining, and many other operations,
  all with amortized logarithmic performance.  Since the trees adapt to
  the sequence of requests, their performance on real access patterns is
  typically even better.  Splay trees are described in a number of texts
  and papers [1,2,3,4,5].

  The code here is adapted from simple top-down splay, at the bottom of
  page 669 of [3].  It can be obtained via anonymous ftp from
  spade.pc.cs.cmu.edu in directory /usr/sleator/public.

  The chief modification here is that the splay operation works even if the
  item being splayed is not in the tree, and even if the tree root of the
  tree is NULL.  So the line:

                              t = splay(i, t);

  causes it to search for item with key i in the tree rooted at t.  If it's
  there, it is splayed to the root.  If it isn't there, then the node put
  at the root is the last one before NULL that would have been reached in a
  normal binary search for i.  (It's a neighbor of i in the tree.)  This
  allows many other operations to be easily implemented, as shown below.

  [1] "Fundamentals of data structures in C", Horowitz, Sahni,
       and Anderson-Freed, Computer Science Press, pp 542-547.
  [2] "Data Structures and Their Algorithms", Lewis and Denenberg,
       Harper Collins, 1991, pp 243-251.
  [3] "Self-adjusting Binary Search Trees" Sleator and Tarjan,
       JACM Volume 32, No 3, July 1985, pp 652-686.
  [4] "Data Structure and Algorithm Analysis", Mark Weiss,
       Benjamin Cummins, 1992, pp 119-130.
  [5] "Data Structures, Algorithms, and Performance", Derick Wood,
       Addison-Wesley, 1993, pp 367-375.
*/
// Some modifications by Johnicholas Hines

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// number of nodes in the tree
// Not actually needed for any of the operations
int size;  

typedef struct tree_node Tree;
struct tree_node {
  Tree* left;
  Tree* right;
  int item;
};

Tree* splay(int i, Tree * t) {
  // Simple top down splay, not requiring i to be in the tree t.
  // What it does is described above.
  Tree* y;
  if (t == NULL) {
    return t;
  }
  Tree N = { NULL, NULL, 0 };
  Tree* l = &N;
  Tree* r = &N;

  for (;;) {
    if (i < t->item) {
      if (t->left == NULL) {
        break;
      }
      if (i < t->left->item) {
        // rotate right
        y = t->left;
        t->left = y->right;
        y->right = t;
        t = y;
        if (t->left == NULL) {
          break;
        }
      }
      // link right
      r->left = t;
      r = t;
      t = t->left;
    } else if (i > t->item) {
      if (t->right == NULL) {
        break;
      }
      if (i > t->right->item) {
        // rotate left
        y = t->right;                          
        t->right = y->left;
        y->left = t;
        t = y;
        if (t->right == NULL) {
          break;
        }
      }
      // link left
      l->right = t;                              
      l = t;
      t = t->right;
    } else {
      break;
    }
  }
  // assemble
  l->right = t->left;                                
  r->left = t->right;
  t->left = N.right;
  t->right = N.left;
  return t;
}

// Here is how sedgewick would have written this.
// It does the same thing.
Tree* sedgewickized_splay (int i, Tree * t) {
  Tree N, *l, *r, *y;
  if (t == NULL) return t;
  N.left = N.right = NULL;
  l = r = &N;
  
  for (;;) {
    if (i < t->item) {
      if (t->left != NULL && i < t->left->item) {
        y = t->left; t->left = y->right; y->right = t; t = y;
      }
      if (t->left == NULL) break;
      r->left = t; r = t; t = t->left;
    } else if (i > t->item) {
      if (t->right != NULL && i > t->right->item) {
        y = t->right; t->right = y->left; y->left = t; t = y;
      }
      if (t->right == NULL) break;
      l->right = t; l = t; t = t->right;
    } else break;
  }
  l->right=t->left; r->left=t->right; t->left=N.right; t->right=N.left;
  return t;
}

Tree* insert(int i, Tree * t) {
  // Insert i into the tree t, unless it's already there.
  // Return a pointer to the resulting tree.
  Tree* new = (Tree *) malloc(sizeof (Tree));
  if (new == NULL) {
    printf("Ran out of space\n");
    exit(1);
  }
  new->item = i;
  if (t == NULL) {
    new->left = new->right = NULL;
    size = 1;
    return new;
  }
  t = splay(i,t);
  if (i < t->item) {
    new->left = t->left;
    new->right = t;
    t->left = NULL;
    size ++;
    return new;
  } else if (i > t->item) {
    new->right = t->right;
    new->left = t;
    t->right = NULL;
    size++;
    return new;
  } else {
    // We get here if it's already in the tree
    // Don't add it again
    free(new);
    return t;
  }
}

Tree* delete(int i, Tree * t) {
  // Deletes i from the tree if it's there.
  // Return a pointer to the resulting tree.
  Tree* x;
  if (t == NULL) {
    return NULL;
  }
  t = splay(i,t);
  if (i == t->item) {
    // found it
    if (t->left == NULL) {
      x = t->right;
    } else {
      x = splay(i, t->left);
      x->right = t->right;
    }
    size--;
    free(t);
    return x;
  }
  // It wasn't there
  return t; 
}

void main() {
  // A sample use of these functions.  Start with the empty tree,
  // insert some stuff into it, and then delete it
  int i;

  Tree* root = NULL; // the empty tree
  size = 0;
  int N;
  assert(scanf("%d\n", &N) == 1);
  for(i = 0; i < N; i++) {
    char ch;
    int u;
    assert(scanf("%c %d\n", &ch, &u) == 2);
    printf("scanned '%c' %d\n", ch, u);
    switch (ch) {
    case 't':
      root = splay(u, root);
      printf((root && root->item == u) ? "YES\n" : "NO\n" );
      break;
    case 'a':
      root = insert(u, root);
      printf("added %d\n", u);
      break;
    case 'd':
      root = delete(u, root);
      printf("deleted %d\n", u);
      break;
    default:
      printf("I didn't understand that.\n");
      break;
    }
  }
  printf("size = %d\n", size);
}

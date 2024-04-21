#ifndef AST_H
#define AST_H


#include "lexer.h"

typedef enum{
  BINARY,
  LITERAL,
  UNARY,
  GROUPING
}ExprType;

typedef struct Expr{
  ExprType type;

}Expr;



#endif /* ifndef AST_H*/


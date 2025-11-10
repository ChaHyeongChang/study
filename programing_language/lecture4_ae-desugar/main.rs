use lalrpop_util::lalrpop_mod ;

pub mod ast ;
use ast::Expr ;
use ast::Expr::{Op, Num, Neg} ;
use ast::Opr::{Add, Sub} ;

lalrpop_mod!(pub ae) ;

fn interp (e: Box<Expr>) -> i32 
{
    match *e {
        Op(l, Add, r) => interp(l) + interp(r),
        Op(l, Sub, r) => interp(l) - interp(r),
        Neg(exp) => -1 * interp(exp),
        Num(n) => n,
    } 
}

fn desugar (e: Box<Expr>) -> Box<Expr>
{
    match *e {
        Op(l, Add, r) => Box::new(Op(desugar(l), Add, desugar(r))), // l과 r에도 desugar를 한번 더 해주는거, 그 결과값을 받은 걸 가지고 새로운 ast노드를 만들어줌
        Op(l, Sub, r) => Box::new(Op(desugar(l), Sub, desugar(r))),
        Neg(e) => Box::new(Op(Box::new(Num(0)), Sub, desugar(e))), // - <expr> => (0 - <expr>) 이걸 ast 수준에서 바꾸는 것
        Num(n) => Box::new(Num(n)), //이건 primitive라 copy된다고 생각하면 됨
    }
}


fn main() 
{   
    let e0 = ae::ExprParser::new().parse("(-(5 - 1) + 3)").unwrap() ;

    println!("e0: {}", e0) ;
    println!("e0 AST: {:?}", e0) ;
    println!("interp(e0): {}", interp(e0.clone())) ; //move로 하면 소유권이 interp로 넘어가서 뒤에서는 e0를 쓸 수 없기 때문에 borrow를 사용함(e0.clone())
    println!("") ;

    let e1 = desugar(e0.clone()) ; //move로 하면 소유권이 interp로 넘어가서 뒤에서는 e0를 쓸 수 없기 때문에 borrow를 사용함(e0.clone())
    println!("e1=desugar(e0): {}", e1) ;
    println!("e1 AST: {:?}", e1) ;
    println!("interp(e1): {}", interp(e1)) ;
}
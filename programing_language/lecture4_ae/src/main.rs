use lalrpop_util::lalrpop_mod ;

pub mod ast ;
use ast::Expr ;
use ast::{add, sub, num} ;
use ast::Expr::{Op, Num} ;
use ast::Opcode::{Add, Sub} ;

lalrpop_mod!(pub ae) ;

fn interp (e: Box<Expr>) -> i32 
{
    match *e {
        Op(l, Add, r) => interp(l) + interp(r), //같은 Op이지만 Op(l, Add, r), Op(l, Sub, r) 안에 들어가는 값의 매칭이 다르기 때문에 매칭이 되는 경우가 구별됨
        Op(l, Sub, r) => interp(l) - interp(r),
        Num(n) => n
    } 
}


fn main() 
{
    let e0 = Box::new( Op( Box::new( Op(Box::new( Num(5) ),  //예제로 썼던 걸 AST를 직접 만드는 경우
                                     Sub, 
                                     Box::new( Num(1) )) 
                                    ), 
                           Add, 
                           Box::new( Num(3) ))
                      ) ; // (5 - 1) + 3 이라는 일종의 트리형태를 e0가 가리킨다.
    println!("e0: {}", e0) ;
    println!("interp(e0): {}", interp(e0)) ;
    println!("") ;

    let e1 = add(sub(num(5), num(1)), num(3)) ;   // AST를 만드는 함수를 만드는 경우 (ast.rs에 정의해놔서 이렇게 사용가능)
    println!("e1: {}", e1) ;
    println!("interp(e1): {}", interp(e1)) ;
    println!("") ;

    let e2 = ae::ExprParser::new().parse("((5 - 1) + 3)").unwrap() ; //string을 넣어주고 pasing해서 쓰는 경우 , unwrap(): 파싱 실패 시 panic. 실제 앱이라면 match나 ?로 오류 처리 권장.
	println!("e2: {}", e2) ;
    println!("interp(e2): {}", interp(e2)) ; //interpreter : 프로그램을 실행시켜줌 그 프로그램에 해당하는 값을 찾는 거다.
}
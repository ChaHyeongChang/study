use ExprType::Num ;
use ExprType::Expr ;
use Opr::Plus ;
use Opr::Product ;

enum Opr {
    Plus,
    Product
}

enum ExprType {
    Num(i32),
    Expr(Box<ExprType>, Opr, Box<ExprType>) //Box는 malloc에 해당, <ExprType>을 갖고, Opr타입을 갖고, 또 다시 <ExprType>을 갖는것  포인터를 만드는것 ---> 일종의 튜플
}

//(Num(1), Plus, (Num(2), Product, Num(3))); 이런 종류의 프로그래밍이 가능 (추후에 배움)

fn eval (e: &ExprType) -> i32 {
    match e {
        Num(n) => *n,
        Expr(l, Plus, r) => eval(l) + eval(r),
        Expr(l, Product, r) => eval(l) * eval(r),
    }
}

fn main () 
{
    let e = Expr(Box::new(Expr(Box::new(Num(3)), Product, Box::new(Num(2)))), Plus, Box::new(Num(2))) ;

    println!("{}", eval(&e)) ;
}
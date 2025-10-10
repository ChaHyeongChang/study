use std::fmt ;

#[derive(Debug, Clone)] //Rust에서 struct나 enum에 대해 일부 기능(Trait)을 직접 구현하지 안하도 자동으로 만들어 주는 기능
pub enum Expr { // c의 enum은 그냥 constant들을 쭉 정의하는거고 Rust의 enum은 타입 여러개 서로 다른 형태를 union 해서 쓰는 것. struct처럼 하나의 union에 (맴버에) primitive(원시 타입)나 다른 타입들을 argument로 넣을 수 있다.
    Num(i32),  //Expr은 Num이거나
	//Op(Expr, Opcode, Expr), 코드를 이렇게 사용한다면 expr의 크기가 무한히 커야함(Expr안에 Expr있고 또 Expr안에 Expr있어서...) 따라서 Expr의 크기를 결정할 수 없다.
	//Rust에ㅐ서는 모든 타입의 크기가 컴파일 시점에 결정되어야 하는데 Expr안에 Expr을 직접 포함하면 크기를 계산할 수 없어서 컴파일이 불가능함
	/*
	ex)
	struct a {
			int n;
			struct a next; //struct a안에 또 struct a있고 이런식으로 ... 따라서 struct의 크기를 정할 수 없다.
			//만약 해결하고 싶으면 포인터로 해라
			//struct a * next;
	};
	 */
    Op(Box<Expr>, Opcode, Box<Expr>), //Box<Expr>, Opcode, Box<Expr>을 가진다.
	//Box는 Expr을 가지는 Heap의 공간, 따라서 Box라고 불림
	//Rust에서 포인터에 해당하는 건 reference, reference는 이미 있는것들에 대해서 포인터 값을 가져서 지칭하는거고
	//Heap 메모리에 새로운 메모리를 잡으면서 그 주소를 포인터를 가지는 방식이 Box임!!!

	//지피티 추가 설명 : “Box는 데이터를 Heap에 저장하고, 그 주소(포인터) 를 Stack에 보관하는 스마트 포인터 타입이다.”


	//Box는 Expr을 가지는 Heap의 공간, 따라서 Box라고 불림
	//Box는 < > 타입을 자기의 데이터 타입으로 가지는데 데이터 타입에 따라서 어떤 애들은 primitive를 가질수도 있고 다른 struct를 가질수도 있다. 위의 경우에는 Expr을 가짐
	//Box<Expr> 이 경우에는 Expr의 Heap 공간에 Expr을 하나 둔 포인터 타입이다. //지피티 추가 설명 : Box<Expr> 가 “Heap 공간에 Expr을 하나 두고, 그 주소를 가진다”
}

#[derive(Debug, Copy, Clone)]
pub enum Opcode { //여기 enum은 그냥 constant Add, Sub
    Add,
    Sub,
}

// Expr ::= Num | (Expr + Expr) | (Expr - Expr)  // 앞으로는 이걸 Expr ::= Num | (Expr Opcode Expr) 이렇게 Opcode 하나로 표현함
// Num ::= [0-9]+
// Opcode ::= '+' | '-'

//pub type ExprBox = Box<Expr> ;

pub fn add (l: Box<Expr>, r: Box<Expr>) -> Box<Expr> 
{
    Box::new(Expr::Op(l, Opcode::Add, r))
}

pub fn sub (l: Box<Expr>, r: Box<Expr>) -> Box<Expr>
{
    Box::new(Expr::Op(l, Opcode::Sub, r))
}

pub fn num (n: i32) -> Box<Expr>
{
    Box::new(Expr::Num(n))
}


//Display 는 "{}"을 썼을 때 안에 값으로 뭐가 들어가야 되냐를 나타냄
impl fmt::Display for Expr 
{
	fn fmt (&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			Expr::Num(n) => write!(f, "{}", n),
			Expr::Op(l, op, r) => write!(f, "({} {} {})", l, op, r)
		}
	}
}

impl fmt::Display for Opcode 
{
	fn fmt (&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			Opcode::Add => write!(f, "+"),
			Opcode::Sub => write!(f, "-")
		}
	}
}
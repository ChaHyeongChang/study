
//Rust에서는 enum이 union의 역할을 받았다 -> type을 프로그래밍하기 좋음, 상수도 추가할 수 있음
//내가 원하는 종류의 타입을 프로그래밍하고 그 타입을 바탕으로 내 프로그램을 규정해나감


enum Solution {
    Double(f64, f64),
    Single(f64),
    NoSolution,
}

//Solution = f64x64 U f64 U {NoSolution} (합집합)

//c에서는 union과 비슷함
/*
union int_or_double {
    int i;
    double d;
}
//
//union int_or_double = int U double (int 합집합 double)
//
//struct int_and_double {
// int i;
// double d;
//}
//
//struct int_and_double = int X double (쌍으로 만든다)
//
//union int_or_double v;
//v.i = 0;
//v.d = 1.d;
//struct에서는 값이 개별적으로 취급되지만 union 에서는 int이거나 double로 표현됨

*/
fn quad (a : f64, b : f64, c : f64) -> Solution 
{
    if a == 0.0 {
        Solution::Single(-1.0 * c / b)
    }
    else if b*b - 4.0 * a * c < 0.0 {
        Solution::NoSolution 
    }
    else if b * b == 4.0 * a * c {
         Solution::Single(-1.0 * b / (2.0 * a)) 
    }
    else {
        Solution::Double((-1.0 * b + (b*b - 4.0 * a * c).sqrt()) / (2.0 * a), 
                         (-1.0 * b - (b*b - 4.0 * a * c).sqrt()) / (2.0 * a))
    }
}

fn main () 
{
    let s : Solution ;
    s = quad(1.0, 2.0, 1.0) ; //1.0*x^2 + 2.0*x + 1.0 

    match s {
        Solution::NoSolution => println!("Unsolvable"), //만약 이 경우를 까먹고 안적었다면 컴파일 오류가 남
        //타입 검사해주는 의미 (프로그램을 만들다가 경우의 수가 더 추가될 것을 대비해서)
        //타입을 만든다는건 사람이 자기 코드를 스스로 제약 하게끔 프로그래밍을 하는 것(제약을 한다는 것은 타입을 만들면 타입은 저 위치에 있지만 저 위치에만 영향을 미치는 것이 아니라 프로그램 전체에 영향을 미침 그러한 어떤 조건을 프로그래밍을 함 따라서 여러군데 나눠 짜는 코드들이 일관성을 가지게 함)
        Solution::Single(x) => println!("{}", x),
        Solution::Double(x, y) => println!("{}, {}", x, y)
        //_ => () 만약 이렇게 적었다면 돌아는 가긴 함(모든 경우에 대해서 적었으니까)
    }
}
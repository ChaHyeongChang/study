fn double (p: (i32, i32)) -> (i32, i32)
{
	(p.0 * 2, p.1 * 2)// (p.0(0번) * 2, p.1(1번) * 2) 
}
/*
fn double (p: Point2D) -> Point 2D
{
    let x = p.0;
    let y = p.1;

    Point2d(x, y);
}
*/

// rust에서 괄호는 거의 튜플을 의미한다!!

*/
fn main () {
	let p1 = (10, 20) ;
	let p2 = double(p1) ;
    //let (x, y) = double(p1);

	println!("x: {}, y: {}", p2.0, p2.1) ;

    //println!("x: {}, y: {}", x, y) ;
}


/*
fn double (p: Point2D) -> Point 2D
{
    let x = p.x;
    let y = p.y;

    Point2d(x:x, y:y);
}
*/
/*
fn main () {
	let p1 = Point2D{x:3, y:4};
    let p2 = double(p1);

	println!("x: {}, y: {}", p2.x, p2.y) ;

}


/*
struct Point2D(i32, i32) ;
*/

/*
struct Point2D {
	x: i32,
	y: i32, (콤마가 남아있어도 괜찮음)
} 
*/
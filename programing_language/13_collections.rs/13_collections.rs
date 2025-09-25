fn main () {
	let arr1 = [1, 2, 3, 4, 5] ;
    let y = arr1[0]; //let y = arr1[5]; ->이렇게 하면 오류
    //array의 특징 : 같은 타입의 값들만 모아서 만들 수 있다
    println!("{}", y);
	let slice1 = &arr1[2..4] ; //slice : array를 일부분만 사용하고 싶을 때 사용

	println!("slice: {:?}", slice1) ; //slice : array를 일부분만 사용하고 싶을 때 사용

	/*
	let mut vec1 : Vec<&str> = Vec::new() ; //Vec<&str> 벡터를 이루는 값이 어떤 타입인지 알려줘야 함
	let mut vec2 = vec![11, 12, 13] ;

	vec1.push("A") ;
	vec1.push("B") ;
	vec1.push("C") ;

	vec2.push(14) ;
	vec2.push(1500) ;

	for e in vec1 {
		print!("{} ", e) ;
	}
	println!("") ;
	*/
}
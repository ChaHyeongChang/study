fn main () {
	let a : i32 = 42 ; //primitive variable은 move를 하지않고 copy를 함 (따라서 소유권이라는 개념이 옮겨질 필요가 없다)
	let b : Box<i32> = Box::new(a) ; // b라는 것은 Box<i32>는 i32를 가지는 heap공간에 대한 reference 이다. Box라기 보다는 Box를 가리키는 reference
	println!("{a}") ; // 이렇게 써도 이 변수 값이랑 같은 값을 출력하게 해줌
	println!("{}", *b) ; //*b는 Box<i32>가 가리키는 힙 안의 값(=42) 을 가져옵니다.
    //println!("{}", b) ; 이렇게 하면 b값 출력(b에 대한 포인터 값이 나오는게 아니라 reference로써 b가 가리키는 box위치에 담긴 값이 가져오게됨


/*
    ✅ 핵심 차이 정리
표현	        의미	                                    출력 결과
b	    Box 스마트 포인터 (Box<i32>)	    내부 값 42 출력 (자동 Deref + Display 위임)
*b	    Box가 가리키는 실제 값 (i32)	    42 출력
&b	    Box 포인터 자체의 스택 주소	        예: 0x7ffeefbff568
{:p}	포인터 형식으로 출력	            {:p}, &*b 등 사용 시 실제 힙 주소 출력
*/

	/*
    //let mut b : Box<i32> = Box::new(a) ;
	*b = *b + 1 ; //기본적으로는 b가 immutable이라 안됨, 위처럼 mutable로 만들어주면 가능
	println!("{}", *b) ;
	*/

    //let c : Box<i32> = b; 
    //println!("{b}") ; //이렇게 하면 오류, move가 되므로 (Box::new(a)의소유권이 이미 c한테 넘어감)
	//println!("{c}") ;
	/*
	let c : &mut Box<i32> = &mut b ; //만약 b가 계속 소유권을 가지고 있게 하고 싶다면 이렇게 사용 --> c는 b의 주소를 reference하게됨 (b를 통해서 Box에 가게된다)
    reference에 대한 reference임!!
	//println!("{b}") ;
	println!("{c}") ;

	**c = 63 ; //c를 통해서 값을 업데이트 하고 싶다면 // *c는 b를 가리킴, **c는 b가 가리키는 값을 63으로 바꿔줌 하지만 이렇게 하고 싶을 때에는 이렇게 let c : &mut Box<i32> = &mut b ; mutable로 해줘야함!!!
    // 추가적으로  let mut c : &mut Box<i32> = &mut b ; 이런식으로 mutable한 variable 이면서도 이걸 값을 업데이트 할 수 있게 만들 수는 없다. (c가 직접 Box 내부의 값을 바꾸는 것을 불가능하다.)
	println!("{c}") ;
	*/
}
//사용자로부터 integer 하나를 입력받아서 int값으로 바꾼 다음에 화면에 출력하는 코드
use std::io

fn main ()
{
    let mut input = String::new();

    io::stdin().read_line(&mut input); //엔터칠 때까지 한 줄을 입력받음, input의 reference를 borrow 해줌

    /*
    let r : i32 = input.trim().parse(); //trim은 사용자로부터 입력받은 string에는 스페이스바나 탭, 엔터 같은 컨트롤캐릭터들이 붙어 있음, 걔네들을 나중에 숫자로 바꾸면 혼란스러우니까 컨트롤 캐릭터들을 앞 뒤로 다 제거해주는 기능
    //parse는 리턴하는 함수마다 다르게 구현되어 있는데 i32로 return값을 가지게 pasing해주세요 하면 숫자값으로 pasing이 되어서 r값에 들어가게됨.
    println!("{}", r);

    //위의 코드를 실행하게 되면 오류가 뜸
    //Pasing을 항상 성공할 수는 없다. 예로 숫자가 들어와야 하는데 알파벳이 들어간다면 pasing이 실패가 됨
    //그런 예외적인 상황에서 error가 생김
    //이런걸 Rust에서 알려주기 위해서 return할 때 result라는 타입으로 리턴함
    */
    //Result가 Okay인 경우와 error인 경우 두개로 나눠서 받음

    let r : Result<i32, std::num::ParseIntError> = input.trim().parse(); //따라서 Result를 사용하고 Result는 타입 두개로 선언이 됨. (i32 이거나 ParseIntError 라는 에러 코드 둘 중에 하나가 나옴 --> 얘도 일종의 enum : 결과 값이 올바른 값이거나 에러 값이므로)

    match r {
        Ok(n) => {println!("{}", n)},
        Err(_) => { println!("Error")}, // _ 는 어떤 타입이든 상관없다는 것을 의미
    }

    //println!("{:?}", r); // :? 디버그로 출력


    /*
    
    //만약 무조건 결과값이 제대로 pasing되는 경우라고 생각하고 출력하려고 하면 unwrap() 사용!!
    //잘못된 값을 입력하면 ex)abc unwrap()이 panic을 일으킴 panic은 runtime 에러에 해당됨

    let r : i32 = input.trim().parse().unwrap();
    println!("{}", r);
    */
} 
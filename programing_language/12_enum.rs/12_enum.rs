enum ThingsInTheSky {
    Sun,
    Stars,
    //이 두가지는 Sun, Star라는 아이덴티파이로 쓰지만 ThingsInTheSky의 두가지 value임 
    //type : 값의 가능성, 변수가 가질 수 있는 모든 값들의 집합
}

fn create_skystate(time: i32) -> ThingsInTheSky {
    /*
    if 6 <= time && time <= 18 {
        ThingsInTheSky::Sun //콜론 두개는 멤버를 지칭할때 사용
    }
    else {
        ThingsInTheSky::Stars
    }
    */
    match time { //match는 if 와 일면 비슷함(위의 주석과 같음), switch case와도 비슷함
        6..=18 => ThingsInTheSky::Sun, //x..y 수학적으로 [6.. 18)과 같은 의미
        _ => ThingsInTheSky::Stars, // _는 default 나머지 모든 값을 의미
    }
    
}

fn check_skystate (state: &ThingsInTheSky) -> () { // () 은 유닛 (아무것도 리턴 안하는건 유닛을 리턴하는거다)
    match state {
        ThingsInTheSky::Sun => println!("I can see the sun!"), //RUST에서는 모든 statement도 익스텐션이다(값으로 쓸 수 있다.)
        ThingsInTheSky::Stars => println!("I can see the stars!")
    }
}


fn main() {
    let time = 8; 
    let skystate : ThingsInTheSky = create_skystate(time); 
    check_skystate(&skystate);
}
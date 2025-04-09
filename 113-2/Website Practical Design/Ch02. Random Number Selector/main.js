$( function(){
    $("input").on("click", function () { 
        // alert("Hi");
        // 把 H1 的內容改成 "Hello"
        // $("h1").text("Hello");
        // 把 h1 的內容換成第一個的li的內容
        // $("h1").text($("li:first").text());
        // 把 h1 的內容換成第二個的li的內容
        // $("h1").text($("li:eq(1)").text());
        var numberOfListItem = $("li").length;
        // var randomChildNumber = Math.floor(Math.random()*numberOfListItem);
        // console.log(randomChildNumber);
        // $("h1").text($("li").eq(randomChildNumber).text());

        // 按下按鈕後執行 10000 次，並將結果顯示在畫面上
        var count = [0, 0, 0];
        
        for (var i = 0; i < 10000; i++) {
            var randomChildNumber = Math.floor(Math.random() * numberOfListItem);
            count[randomChildNumber]++;
        }

        var cnt = 0;
        $("li").each(function() {
            $(this).append(" <span>" + count[cnt] + "</span>");
            ++cnt;
        });
    });
})
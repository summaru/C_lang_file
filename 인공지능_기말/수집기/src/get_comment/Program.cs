using System;
using System.Collections.Generic;
using System.IO;
namespace get_comment
{
    class Program
    {
        static string url = "https://www.youtube.com/watch?v=PVcpF7J2oXs";
        static int pageDown = 5;
        static int timeout = 60;
        static void Main(string[] args)
        {
            
            Intro();
            if(!GetInput())return;
            Console.WriteLine(url);

            Client c = new Client(url,pageDown);
            var d = c.Dirver;
            Output file_out = new Output();
            Queue<string> q;
            try
            {
                q = c.StartGetComments(timeout);
            }
            catch(Exception)
            {
                d.Close();
                Console.WriteLine("댓글 데이터들이 탐지 되지 않습니다.");
                return;
            }
 

            file_out.Start("."+Path.DirectorySeparatorChar+"_comment.txt",q);
            c.Wait();
            file_out.Close();
            Console.WriteLine("");
            Console.WriteLine("끝났습니다");
            Console.Write("Press <Enter> to exit... ");
            while (Console.ReadKey().Key != ConsoleKey.Enter) { }
        }

        static void Intro()
        {
            Console.WriteLine("인공지능 기말고사 과제, 유튜브 댓글 수집기");
            Console.WriteLine("version : 0.1.0");
            Console.WriteLine("20162904 안성근");
            Console.WriteLine("필요 의존성 프로그램:firefox, geckodriver");
            Console.WriteLine("주의점:비정상적인 종료가 일어날경우, firefox 프로세스가 종료 되지 않고" + 
            "계속 살아있을수 있습니다," +"그럴경우 작업관리자로 종료 해주세요");
            Console.WriteLine("주의점2:실행중 콘솔창 크기를 조절할 경우 에러가 날수 있습니다.");
            
        }
        static Boolean GetInput()
        {
            try
            {
                Console.Write("최소한 받을 코맨트를 입력하세요(오차가 있을수 있습니다,기본값:{0})",pageDown);
                
                string rawp = Console.ReadLine();
                
                if(!rawp.Equals(""))
                {
                    int p = int.Parse(rawp);
                    if(p > 0)
                    {
                        pageDown = p;
                    }
                }
                
            }catch(Exception)
            {
                
                Console.WriteLine("숫자로 변환이 안됩니다. 숫자로 입력하세요");
                return false;
            }
            Console.Write("수집할 유튜브 url를 입력하세요(기본값:{0})",url);
            var str = Console.ReadLine();
            if(!str.Equals(""))
            {
                url = str;
            }
            
           

            return true;
        }
    }
}

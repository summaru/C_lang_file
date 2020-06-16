using System;
using System.Collections.Generic;
using System.IO;
namespace get_comment
{
    class Program
    {
        //static string url = "https://www.youtube.com/watch?v=PVcpF7J2oXs";
        //static int pageDown = 5;
        static int timeout = 60;
        static string dataFileName = "yData.html";
        static void Main(string[] args)
        {

            if (args.Length < 3)
            {
                Console.Error.WriteLine("첫번째 인자는 url,두번째 인자는 불려올 댓글 페이지숫자를 입력하세요");
                return;
            }
           
            Console.WriteLine("입력받은 url="+args[0]);
            string url = args[0];
            int pageLoad;
            string downloadPath = args[2];

            try
            {
                pageLoad = int.Parse(args[1]);
            }catch(Exception)
            {
                Console.WriteLine("두번째 인자는 숫자로 입력하세요");
                return;
            }


            Client c = new Client("https://www.youtube.com/watch?v=PVcpF7J2oXs",pageLoad);
            var d = c.Dirver;
            string source;
            try
            {
                source = c.StartGetHTML(timeout);
            }
            catch(Exception)
            {
                d.Close();
                Console.WriteLine("댓글 데이터들이 탐지 되지 않습니다.");
                return;
            }

            WriteDataFile(source, downloadPath);
            Console.WriteLine("html 데이터 불려오기 성공");

        }

        private static void WriteDataFile(string source,string path)
        {

            using(var stream = File.Open(path, FileMode.Create))
            {
                using(var wStream =new StreamWriter(stream))
                {
                    wStream.Write(source);
                }
            }
        }
        
    }
}

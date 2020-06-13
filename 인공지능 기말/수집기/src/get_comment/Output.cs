using System;
using System.Text;
using System.IO;
using System.Collections.Generic;
using System.Threading;

namespace get_comment 
{
    class Output
    {
        private Queue<string> cache = null;
        private FileStream fStream = null;
        private Thread subFileThead;
        
        private int current;
        public Output()
        {
            subFileThead = new Thread(new ThreadStart(this.WriteFile));
            
        }
        private void WriteFile()
        {
            string buf = "";

            var c = cache;
            
            byte[] byteD;
            while(true)
            {
                if(State.SpanListEnd)
                {
                    
                    while (c.TryDequeue(out buf))
                    {
                        byteD = Encoding.UTF8.GetBytes(buf+Environment.NewLine);
                
                        fStream.Write(byteD,0,byteD.Length-1);
                
                        current++;
                    }
                    State.FileEnd = true;
                    break;
                }
                if(!c.TryDequeue(out buf)) {continue;}
                byteD = Encoding.UTF8.GetBytes(buf+Environment.NewLine);
                
                fStream.Write(byteD,0,byteD.Length-1);
                
                current++;
            }
        }
        private void OutputCmd()
        {
            int prev = 0;
            int left = Console.CursorLeft;
            int top = Console.CursorTop;
            while(!State.FileEnd)
            {
               
                if(current == prev)continue;
                Console.SetCursorPosition(left,top);
                Console.Write("write data to file(실행하는동안 해당파일에 접근이 안될수도 있습니다.) 문장갯수:{0}",
                    current);
            }
        }
        public void Start(string path,Queue<string> q)
        {
            cache = q;
            
            fStream = File.Open(path,FileMode.Create,FileAccess.Write,FileShare.Read);

            
            subFileThead.Start();
            new Thread(new ThreadStart(OutputCmd)).Start();
        }
        public void Close()
        {
            subFileThead.Join();       
            fStream.Close();
        }
    }
}
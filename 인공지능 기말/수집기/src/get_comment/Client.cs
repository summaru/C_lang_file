using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using System.Threading;

namespace get_comment
{
    
    class Client
    {
        private int downCount=0;
        private IWebDriver driver;
        private Thread t;

        private string url;
        private int cutLine;
        public IWebDriver Dirver 
        {
            get
            {
                return driver;
            }
        }
       
        public Client(string url,int scrollDown,int firstStartLen)
        {
            downCount = scrollDown;
            FirefoxOptions options = new FirefoxOptions();
            options.AddArgument("--headless");
            driver = new FirefoxDriver(options);
            this.url = url;
            cutLine = firstStartLen;
        }

        public Queue<string> StartGetComments()
        {
            try 
            {
                driver.Navigate().GoToUrl(url);
            }
            catch(Exception e)
            {
                throw e;
            }
            int left = Console.CursorLeft;
            int top = Console.CursorTop;
            IJavaScriptExecutor js = (IJavaScriptExecutor) driver;
            var h = driver.Manage().Window.Size.Height;//js.ExecuteScript("innerHeight");
            var h2 = h;
            for(int i=0;i<downCount;)
            {   
                i++;
                Console.SetCursorPosition(left,top);
                Console.Write("Loading Youtube Video Comment : {0}%",Math.Round((double)i * 100.0/(double)downCount));
                
                js.ExecuteScript(
                    string.Format("window.scrollTo(0, {0})",h2)
                );
                h2 = h2+h;
                //driver.FindElement(By.TagName("body")).SendKeys(Keys.End);
            }
            Console.Write(Environment.NewLine);
            List<ReadOnlyCollection<IWebElement>> list = new List<ReadOnlyCollection<IWebElement>>();
            ReadOnlyCollection<IWebElement> commentLayouts;
            try
            {
               
                var globalBox = driver.FindElement(By.TagName("ytd-comments"));
                commentLayouts = globalBox.FindElements(
                    By.TagName("ytd-comment-thread-renderer"));

               
            }
            catch(Exception e) 
            {
                throw e;
            }
            
            
            var boxQ = FilterContentBox(commentLayouts);
            Console.WriteLine("");
            Console.WriteLine("댓글 상자들을 일정 부분 불려오고 있습니다...");
            while(true){if(boxQ.Count > cutLine){break;}}

            

            var res = new Queue<string>();
            IWebElement buf;
            ReadOnlyCollection<IWebElement> spans;
            t = new Thread(new ThreadStart( ()=> {
                while(true)
                {
                
                    if(State.ContentTextEnd)
                    {
                        Console.WriteLine("content-text 완료");
                        while(boxQ.TryDequeue(out buf))
                        {
                            spans = buf.FindElements(By.TagName("span"));
                            foreach(var t in spans)res.Enqueue(t.Text);

                        }
                        State.SpanListEnd = true;
                        break;
                    }

                    if(!boxQ.TryDequeue(out buf))continue;
                    spans = buf.FindElements(By.TagName("span"));

                    foreach(var t in spans)
                    {
                        if(t.Text.Equals(""))continue;
                        res.Enqueue(t.Text);
                    }
                }
            } ));
            t.Start();
            return res;
        }

        public void Wait() {t.Join();driver.Close();}
        private Queue<IWebElement> FilterContentBox(ReadOnlyCollection<IWebElement> list)
        {
            var q = new Queue<IWebElement>();
            new Thread(new ThreadStart(() => {
                foreach(var child in list)
                {
                    q.Enqueue(child.FindElement(By.Id("content-text")));
                }
                State.ContentTextEnd = true;
            })).Start();
            return q;
        }
    }

}
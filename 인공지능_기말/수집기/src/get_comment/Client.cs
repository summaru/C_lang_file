using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using System.Threading;
using OpenQA.Selenium.Support.UI;

namespace get_comment
{
    
    class Client
    {
        private int downCount=0;
        private IWebDriver driver;
        private Thread t;

        private string url;
        private IWebElement sectionY;

        int left = 0;
        int top = 0;
        public IWebDriver Dirver 
        {
            get
            {
                return driver;
            }
        }
       
        public Client(string url,int commentCount)
        {
            downCount = commentCount;
            FirefoxOptions options = new FirefoxOptions();
            options.AddArgument("--headless");
            driver = new FirefoxDriver(options);
            this.url = url;
            

            left = Console.CursorLeft;
            top = Console.CursorTop;
        }

        public Queue<string> StartGetComments(double timeout)
        {
            try 
            {
                driver.Navigate().GoToUrl(url);
            }
            catch(Exception e)
            {
                throw e;
            }

            CWrite("wait load sections element");
            WebDriverWait wait = new WebDriverWait(driver, TimeSpan.FromSeconds(timeout));

            sectionY = wait.Until<IWebElement>(d =>
                { return d.FindElement(By.Id("sections")); }
            );
            

            Console.Write(Environment.NewLine);
            List<ReadOnlyCollection<IWebElement>> list = new List<ReadOnlyCollection<IWebElement>>();
            IWebElement globalBox;
            try
            {
               
                globalBox = driver.FindElement(By.TagName("ytd-comments"));
                

               
            }
            catch(Exception e) 
            {
                throw e;
            }
            
            
            var boxQ = FilterContentBox(globalBox, By.TagName("ytd-comment-thread-renderer"));
           


            

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
        private Queue<IWebElement> FilterContentBox(IWebElement parent,By by)
        {
            ReadOnlyCollection<IWebElement> list;
            IJavaScriptExecutor js = (IJavaScriptExecutor)driver;
            int cut = 0;
            MoveTo(js, getSectionY());
            do
            {
                

                list = parent.FindElements(
                    By.TagName("ytd-comment-thread-renderer"));
               
                CWrite("최소치까지 불려오는 중입니다: "  + (list.Count).ToString()+"개");
                if(list.Count != cut)
                {
                    MoveTo(js, getSectionY()); 
                    
                    cut = list.Count;
                }
                //리눅스 제한
                Thread.Sleep(1000);
            } while (list.Count < downCount);
            Console.WriteLine("");
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

        private void MoveTo(IJavaScriptExecutor js,int height)
        {
            js.ExecuteScript(
                    string.Format("window.scrollTo(0, {0})", height)
            );
            
        }

        private void CWrite(string msg)
        {
            Console.SetCursorPosition(left, top);
            Console.Write(msg);
        }


        private int getSectionY()
        {
            return int.Parse(sectionY.GetAttribute("offsetTop"));
        }
    }

}
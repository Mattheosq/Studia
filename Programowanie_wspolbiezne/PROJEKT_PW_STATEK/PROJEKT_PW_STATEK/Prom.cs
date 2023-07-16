using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;

namespace PROJEKT_PW_STATEK
{
    public class Prom
    {
        private Rectangle rect2;
        private Canvas _canvas;
        private Lewy_brzeg _lewy_Brzeg; // obiekt z lista samochodow na lewym brzegu
        public List<Thread> miejsca; // watki obslugujace zaladowanie statku
        public Thread _prom; // watek przemieszczajacego sie promu
        private const int MIN_X = 180; // startowa pozycja statku
        private const int MAX_X = 490; // koncowa pozycja statku
        public Samochod[] samochody; // lista samochodow na statku
        public readonly object _lock1 = new object();




        public Prom(Canvas canvas, Lewy_brzeg lewy_Brzeg)
        {
            _canvas = canvas;
            _lewy_Brzeg = lewy_Brzeg;
            rect2 = new Rectangle
            {
                Stroke = Brushes.DarkGray,
                StrokeThickness = 2
            };
            Canvas.SetLeft(rect2, MIN_X);
            Canvas.SetTop(rect2, 220);
            rect2.Width = 130;
            rect2.Height = 35;
            rect2.Fill = Brushes.DarkGray;

            _prom = new Thread(new ThreadStart(() => Przemieszczanie()));
            miejsca = new List<Thread>();
            samochody = new Samochod[3];
            for (int i = 0; i < 3; i++)
            {
                int v = i;
                miejsca.Add(new Thread(new ThreadStart(() => Watek_Miejsce(v))));

                miejsca[i].Start();

            }
            _prom.Start();


            canvas.Children.Add(rect2);



        }
        ~Prom()
        {
            _canvas.Dispatcher.BeginInvoke(new Action(() => { _canvas.Children.Remove(rect2); }));
        }

        public void Move(int target, int duration)
        {

            _canvas.Dispatcher.BeginInvoke(new Action(() =>
            {
                var moveAnimX = new DoubleAnimation(Canvas.GetLeft(rect2), target, new Duration(TimeSpan.FromSeconds(duration)));
                rect2.BeginAnimation(Canvas.LeftProperty, moveAnimX);
            }));

        }


        public double getX()
        {
            double x = 0;
            _canvas.Dispatcher.Invoke(new Action(() => { x = (double)Canvas.GetLeft(rect2); }));
            return x;
        }

        public void Watek_Miejsce(int i) // pojedyncze miejsce
        {
            Samochod samochod = null;

            while (true)
            {

                //Thread.Sleep(5000); // czas na dojazd na prom
                if (samochody[i] != null)
                    continue;
                lock (_lock1)
                {
                    samochod = _lewy_Brzeg.Deq(); // proba pobrania samochodu z brzegu
                    if (samochod != null)
                    {
                        samochody[i] = samochod;
                        samochody[i].MoveX(190 + i * 40,0.01f);
                        samochody[i].setY(190);
                        Monitor.Pulse(_lock1);
                    }
                }

            }

        }


        public void Przemieszczanie()
        {

            while (true)
            {

                //Thread.Sleep(3000);
                lock (_lock1)
                {
                    bool b = true;
                    for (int i = 0; i < 3; i++)
                    {
                        if (samochody[i] != null)
                            b = false;
                    }

                    if (b)
                        continue; // jesli wszystkie miejsca sa puste, to statek nie plynie
                    Stopwatch sw = Stopwatch.StartNew();
                    while (sw.ElapsedMilliseconds <= 4000)
                    {
                        bool c = true;
                        for (int i = 0; i < 3; i++)
                        {
                            if (samochody[i] == null)
                                c = false;
                        }

                        if (c)
                            break;// jezeli wszystkie miejsca sa zapelniane, statek plynie od razu
                        Monitor.Wait(_lock1, TimeSpan.FromMilliseconds(4000 - sw.ElapsedMilliseconds));
                    }

                    Thread.Sleep(500);
                    for (int i = 0; i < 3; i++)
                    {
                        if (samochody[i] != null)
                            samochody[i].MoveX(500 + 40 * i, 4);

                    }

                    Move(MAX_X, 4);
                    Thread.Sleep(5000);// czas na przeplyniecie w jedna strone

                    for (int i = 0; i < 3; i++)
                    {
                        if (samochody[i] != null)
                            samochody[i].Hide();
                        samochody[i] = null;
                    }

                    Move(MIN_X, 4);
                    Thread.Sleep(4000); // czas na przeplyniecie w druga strone

                }
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows;
using System.Windows.Media.Animation;

namespace PROJEKT_PW_STATEK
{
    public class Samochod
    {
        private Rectangle rect;
        private Canvas _canvas;

        public Samochod(Canvas canvas)
        {
            _canvas = canvas;
            Application.Current.Dispatcher.Invoke(() => {

                rect = new Rectangle
                {
                    Stroke = Brushes.LightBlue,
                    StrokeThickness = 2
                };
                Canvas.SetLeft(rect, 10);
                Canvas.SetTop(rect, 10);
                rect.Width = 30;
                rect.Height = 30;
                rect.Fill = Brushes.Green;


                canvas.Children.Add(rect);
            });

        }
        ~Samochod()
        {
            _canvas.Dispatcher.BeginInvoke(new Action(() => { _canvas.Children.Remove(rect); }));
        }

        public void Hide()
        {
            
            _canvas.Dispatcher.BeginInvoke(new Action(() => { rect.Opacity = 0; }));
        }
        public void setX(int x)
        {
            _canvas.Dispatcher.BeginInvoke(new Action(() => { Canvas.SetLeft(rect, x); }));
        }
        public void setY(int y)
        {
            
            _canvas.Dispatcher.BeginInvoke(new Action(() => { Canvas.SetTop(rect, y); }));
        }
        public void MoveX(int target, float duration)
        {
            
            _canvas.Dispatcher.BeginInvoke(new Action(() => {
                var moveAnimX = new DoubleAnimation(Canvas.GetLeft(rect), target, new Duration(TimeSpan.FromSeconds(duration)));
                rect.BeginAnimation(Canvas.LeftProperty, moveAnimX);
            }));
        }
        
    }
    
}

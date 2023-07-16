using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace PROJEKT_PW_STATEK
{

    

    
    public partial class MainWindow : Window
    {

        Samochod samochod;
        //public List<Samochod> samochody = new List<Samochod>();
        Prom prom;
        Lewy_brzeg _carqueue = new Lewy_brzeg();
        
        public MainWindow()
        {
            InitializeComponent();
            prom = new Prom(canvas,_carqueue);

            
            

        }
        

        private void dodajPojazd_Click(object sender, RoutedEventArgs e)
        {
            samochod = new Samochod(canvas);
            _carqueue.Enq(samochod);    
        }

       
    }



}
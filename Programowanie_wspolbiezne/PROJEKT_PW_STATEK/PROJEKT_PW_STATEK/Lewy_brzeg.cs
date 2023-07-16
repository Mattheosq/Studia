using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PROJEKT_PW_STATEK
{
    public class Lewy_brzeg
    {
        public List<Samochod> _queue = new List<Samochod>(); // kolejka samochodow na lewym brzegu

        public void Enq(Samochod samochod)
        {

            
            
                samochod.setX(-50);
                samochod.setY(223);
                samochod.MoveX(150 - 40 * _queue.Count(), 2);
                _queue.Add(samochod);
            
            
        }
        public Samochod Deq()
        {
            
            
                if(_queue.Count() == 0)
                {
                    return null;
                }
                
                Samochod to_be_deleted = _queue.ElementAt(0); // zapisanie pierwszego samochodu z kolejki, zeby przeniesc go na prom
                _queue.RemoveAt(0);
                
                for (int i = 0; i < _queue.Count; i++)
                {
                    _queue.ElementAt(i).MoveX(150 - 40 * i, 2);
                }
                
                
                return to_be_deleted;
            
        
        }

        
    }
}

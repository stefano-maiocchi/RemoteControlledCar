using Blazm.Bluetooth;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.CompilerServices;


namespace RemoteControlledCar.Devices
{
    public class clsCar
    {
        string m_serviceid = "0000ffe0-0000-1000-8000-00805f9b34fb";
        string m_characteristics = "0000ffe1-0000-1000-8000-00805f9b34fb";
        
        protected IBluetoothNavigator Navigator { get; set; }
        public Device Device { get; set; }

        
        // to enable bluetooth in Chrome chrome://flags/#enable-web-bluetooth        
        public clsCar(IBluetoothNavigator navigator)
        {
            this.Navigator = navigator;
        }

        public async void connect()
        {
            var q = new RequestDeviceQuery();            

            q.Filters.Add(new Filter() { Services = { m_serviceid } });
            q.OptionalServices.Add(m_characteristics); //Send service                                    

            try
            {                
                Device = await Navigator.RequestDeviceAsync(q);                

                await Device.SetupNotifyAsync(m_serviceid, m_characteristics);
                Device.Notification += Value_Notification;
            }
            catch (Exception ex) { Console.WriteLine(ex); }            
        }

        public async void send(string frame)
        {
            try
            {                      
                await Navigator.WriteValueAsync(Device.Id, m_serviceid, m_characteristics, System.Text.ASCIIEncoding.ASCII.GetBytes(frame));
            }
            catch(Exception ex) { Console.WriteLine(ex); } ;
        }

        private void Value_Notification(object sender, CharacteristicEventArgs e)
        {
            var data = e.Value.ToArray();                        
        }
    }
}

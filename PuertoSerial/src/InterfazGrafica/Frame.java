
package InterfazGrafica;

import com.panamahitek.ArduinoException;
import com.panamahitek.PanamaHitek_Arduino;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import jssc.SerialPortException;

/**
 *
 * @author Ricardo Andrés Calvo
 */
public class Frame extends JFrame implements ActionListener{
    PanamaHitek_Arduino ino = new PanamaHitek_Arduino();
    boolean isConectado = false;
    JLabel ltitle, lpuerto, ldato, lout;
    JComboBox jcpuertos;
    JTextField tdato;
    JButton bconectar, benviar, bactualizar;
    ImageIcon iactualizar;
    
    public Frame(){  
        
        ltitle = new JLabel("Envio de datos.");
        ltitle.setFont(new java.awt.Font("Dialog", 1, 24));
        ltitle.setHorizontalAlignment(SwingConstants.CENTER);
        
        lpuerto = new JLabel("Puertos disponibles:");
        lpuerto.setFont(new java.awt.Font("Dialog", 0, 14));
        lpuerto.setHorizontalAlignment(SwingConstants.CENTER);
        
        ldato = new JLabel("Dato a enviar:");
        ldato.setFont(new java.awt.Font("Dialog", 0, 14));
        ldato.setHorizontalAlignment(SwingConstants.CENTER);
        
        lout = new JLabel("Envío de datos a una placa Arduino por puerto serial.");
        lout.setFont(new java.awt.Font("Dialog", 0, 14));
        lout.setHorizontalAlignment(SwingConstants.CENTER);
        
        jcpuertos = new JComboBox();
        jcpuertos.setFont(new java.awt.Font("Dialog", 0, 14));
        
        tdato = new JTextField("");
        tdato.setFont(new java.awt.Font("Dialog", 0, 14));
        tdato.addActionListener((ActionListener) this);
         
        bconectar = new JButton("Conectar.");
        bconectar.addActionListener((ActionListener) this);
        bconectar.setFont(new java.awt.Font("Dialog", 0, 14));
        
        benviar = new JButton("Enviar.");
        benviar.addActionListener((ActionListener) this);
        benviar.setFont(new java.awt.Font("Dialog", 0, 14));
        
        iactualizar = new ImageIcon("src/Imagen/actualizar.png");
        
        bactualizar = new JButton(iactualizar);
        bactualizar.addActionListener((ActionListener) this);
        bactualizar.setFont(new java.awt.Font("Dialog", 0, 12));
        
        Image icono = Toolkit.getDefaultToolkit().getImage("src/Imagen/logo.png"); 
        this.setIconImage(icono); 
        
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(lout, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                            .addComponent(bconectar, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(jcpuertos, javax.swing.GroupLayout.PREFERRED_SIZE, 144, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(bactualizar, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addComponent(lpuerto, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(tdato)
                            .addComponent(ldato, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(benviar, javax.swing.GroupLayout.DEFAULT_SIZE, 179, Short.MAX_VALUE)))
                    .addComponent(ltitle, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(59, Short.MAX_VALUE)
                .addComponent(ltitle)
                .addGap(28, 28, 28)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(lpuerto)
                    .addComponent(ldato, javax.swing.GroupLayout.PREFERRED_SIZE, 19, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jcpuertos, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(tdato, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(bactualizar, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(bconectar)
                    .addComponent(benviar))
                .addGap(31, 31, 31)
                .addComponent(lout)
                .addGap(40, 40, 40))
        );
        pack();
        getPorts();  
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == benviar || e.getSource() == tdato){
            if(isConectado == true){
                try {
                    ino.sendData(tdato.getText());
                    lout.setText("Dato enviado correctamente.");
                } catch (ArduinoException | SerialPortException ex) {
                    lout.setText("Error al enviar el dato.");
                    isConectado = false;
                    jcpuertos.setEnabled(true);
                }
            }else{
                lout.setText("No hay conexión establecida a través del puerto serial.");
            }
            tdato.setText("");
        }else if(e.getSource() == bconectar){
            if(isConectado == true){
                try {
                    ino.killArduinoConnection();
                } catch (ArduinoException ex) {
                    lout.setText("No existía conexión por el puerto serial.");
                }finally{
                    bconectar.setText("Conectar.");
                    lout.setText("Conexión interrumpida.");
                    isConectado=false;
                    jcpuertos.setEnabled(true);
                }
            }else{
                try {
                    ino.arduinoTX(jcpuertos.getSelectedItem().toString(), 9600);
                    bconectar.setText("Desconectar.");
                    isConectado = true;
                    jcpuertos.setEnabled(false);
                    lout.setText("Conexión establecida con el puerto serial " + jcpuertos.getSelectedItem().toString() + ".");
                } catch (ArduinoException ex) {
                    lout.setText("Error al conectarse con el puerto serial "+jcpuertos.getSelectedItem().toString());
                }
            }
        }else if(e.getSource() == bactualizar){
            getPorts();
        }
    }
    
    public void getPorts() {
        jcpuertos.removeAllItems();
        if (ino.getPortsAvailable() > 0) {
            ino.getSerialPorts().forEach(i -> jcpuertos.addItem(i));
        }
    }
    
}

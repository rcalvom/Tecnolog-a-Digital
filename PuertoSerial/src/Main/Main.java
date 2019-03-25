
package Main;

import InterfazGrafica.Frame;
import java.awt.Dimension;
import java.awt.Toolkit;
import javax.swing.JFrame;


/**
 *
 * @author Ricardo Andrés Calvo
 */
public class Main {
    public static void main(String[] args) {
        Frame frame = new Frame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setTitle("Enviar datos Arduino");
        frame.setSize(400, 300);
        Toolkit t = Toolkit.getDefaultToolkit();
	Dimension d = t.getScreenSize();
        frame.setBounds(d.width/4, d.height/4, 400, 300);
        frame.setResizable(false);
        frame.setVisible(true);
    }
    
}

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;

class MonitorThread implements Runnable {
    private Process proc;
    MonitorThread (Process pr) {
        proc = pr;
    }

    @Override
    public void run() {
        try {
            Thread.sleep(10000);
            proc.destroy();
        } catch (Exception e) {

        }
    }
}

public class FactorServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            String poly = req.getParameter("poly");
            if (poly != null) {
                Process proc = Runtime.getRuntime().exec("D:/CourseWare/ProgramDesign/Tool_of_Polynomials/Factorization.exe");
                new Thread(new MonitorThread(proc)).start();

                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(proc.getOutputStream()));
                bw.write(poly + "\n");
                bw.close();

                BufferedReader br = new BufferedReader(new InputStreamReader(proc.getInputStream()));
                String temp = null;
                StringBuilder res = new StringBuilder();
                while ((temp = br.readLine()) != null) {
                    res.append(temp + "\n");
                }
                br.close();
                PrintWriter pw = resp.getWriter();
                pw.print(res);
                System.out.println(res);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}

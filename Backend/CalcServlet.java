import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;

public class CalcServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            String poly1 = req.getParameter("poly1");
            String poly2 = req.getParameter("poly2");
            String oper = req.getParameter("oper");
            if (oper != null) {
                System.out.println(poly1 + " " + poly2 + " " + oper);
                Process proc = null;
                if (oper.equals("0")) {
                    proc = Runtime.getRuntime().exec("D:/CourseWare/ProgramDesign/Tool_of_Polynomials/Addition.exe");
                } else if (oper.equals("1")) {
                    proc = Runtime.getRuntime().exec("D:/CourseWare/ProgramDesign/Tool_of_Polynomials/Subtraction.exe");
                } else if (oper.equals("2")) {
                    proc = Runtime.getRuntime().exec("D:/CourseWare/ProgramDesign/Tool_of_Polynomials/Multiplication.exe");
                } else {
                    proc = Runtime.getRuntime().exec("D:/CourseWare/ProgramDesign/Tool_of_Polynomials/Division.exe");
                }

                new Thread(new MonitorThread(proc)).start();

                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(proc.getOutputStream()));
                bw.write(poly1 + "\n" + poly2 + "\n");
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

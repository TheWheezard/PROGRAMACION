package util.test;

import static org.junit.jupiter.api.Assertions.*;

import java.io.IOException;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import util.Database;

class DatabaseTest {

	@BeforeAll
	static void setUpBeforeClass() throws Exception { Database.LoadDriver(); }

	@Test
	void testDbAccess() throws IOException, SQLException {
		
		Connection con = null;
		ResultSet rs = null;
		
		try {
			con = Database.Connection();
			rs = con.createStatement().executeQuery("SELECT Host, User FROM user;");
			
			int i = 0;
			while (rs.next()) {
				System.out.println(rs.getString("Host") + " " + rs.getString("User"));
				i++;
			}
			
			assertEquals(4, i);
		}
		catch (SQLException e) { throw e; }
		finally {
			if (rs != null) rs.close();
			if (con != null) con.close();
		}
	}
}
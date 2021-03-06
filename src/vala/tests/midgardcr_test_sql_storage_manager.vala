using MidgardCR;

void midgardcr_test_add_sql_storage_manager_tests () {

	/* constructor */
	Test.add_func ("/SQLStorageManager/constructor", () => {
		MidgardCR.SQLStorageManager mngr = null;
		MidgardCR.Config config = new MidgardCR.Config ();
		bool manager_fail = false;

		try {
			config.read_configuration (DEFAULT_CONFIGURATION, true);
		} catch (GLib.FileError e) {
			GLib.warning (e.message);
		} catch (GLib.KeyFileError e) {
			GLib.warning (e.message);
		}

		/* FAIL */
		try {
			mngr = new MidgardCR.SQLStorageManager ("", config);
		} catch (StorageManagerError e) {
			manager_fail = true;
		}
		assert (mngr == null);
		assert (manager_fail == true);

		/* SUCCESS */		
		try {
			mngr = new MidgardCR.SQLStorageManager ("test_manager", config);
		} catch (StorageManagerError e) {
			GLib.warning ("Failed to initialize new SQLStorageManager");
		}
		assert (mngr != null);
	});

	Test.add_func ("/SQLStorageManager/open", () => {
		MidgardCR.SQLStorageManager mngr = null;
		MidgardCR.Config config = new MidgardCR.Config ();	

		try {
			config.read_configuration (DEFAULT_CONFIGURATION, true);
		} catch (GLib.FileError e) {
			GLib.warning (e.message);
		} catch (GLib.KeyFileError e) {
			GLib.warning (e.message);
		}

		/* SUCCESS */		
		try {
			mngr = new MidgardCR.SQLStorageManager ("test_manager", config);
		} catch (StorageManagerError e) {
			GLib.warning ("Failed to initialize new SQLStorageManager");
		}
		assert (mngr != null);

		bool opened = false;
		/* SUCCESS */
		try {
			opened = mngr.open ();
		} catch (StorageManagerError e) {
			GLib.warning (e.message);
		}
		assert (opened == true);

		/* SUCCCESS open once again */
		try {
			opened = mngr.open ();
		} catch (StorageManagerError e) {
			GLib.warning (e.message);
		}
		assert (opened == true);			 
	});

	Test.add_func ("/SQLStorageManager/close", () => {
		MidgardCR.SQLStorageManager mngr = null;
		MidgardCR.Config config = new MidgardCR.Config ();
		bool closed = false;
		bool opened = false;

		try {
			config.read_configuration (DEFAULT_CONFIGURATION, true);
		} catch (GLib.FileError e) {
			GLib.warning (e.message);
		} catch (GLib.KeyFileError e) {
			GLib.warning (e.message);
		}

		/* SUCCESS */		
		try {
			mngr = new MidgardCR.SQLStorageManager ("test_manager", config);
		} catch (StorageManagerError e) {
			GLib.warning ("Failed to initialize new SQLStorageManager");
		}
		assert (mngr != null);

		/* FAIL */
		try {
			closed = mngr.close ();
		} catch (MidgardCR.StorageManagerError e) {
			closed = false;
		}
		assert (closed == false);

		/* SUCCESS */
		try {
			opened = mngr.open ();
		} catch (StorageManagerError e) {
			GLib.warning (e.message);
		}
		assert (opened == true);

		/* SUCCESS */
		try {
			closed = mngr.close ();
		} catch (MidgardCR.StorageManagerError e) {
			GLib.warning (e.message);
		}
		assert (closed == true);
	});

	Test.add_func ("/SQLStorageManager/initialize_storage", () => {
		MidgardCR.SQLStorageManager mngr = null;
		MidgardCR.Config config = new MidgardCR.Config ();	

		try {
			config.read_configuration (DEFAULT_CONFIGURATION, true);
		} catch (GLib.FileError e) {
			GLib.warning (e.message);
		} catch (GLib.KeyFileError e) {
			GLib.warning (e.message);
		}

		/* SUCCESS */		
		try {
			mngr = new MidgardCR.SQLStorageManager ("test_manager", config);
		} catch (StorageManagerError e) {
			GLib.warning ("Failed to initialize new SQLStorageManager");
		}
		assert (mngr != null);

		bool opened = false;
		/* SUCCESS */
		try {
			opened = mngr.open ();
		} catch (StorageManagerError e) {
			GLib.warning (e.message);
		}
		assert (opened == true);

		bool storage_initialized = false;
		/* SUCCESS */
		try {
			storage_initialized = mngr.initialize_storage ();
		} catch (MidgardCR.StorageManagerError e) {
			GLib.warning (e.message);
		}
		assert (storage_initialized == true);
	});

	Test.add_func ("/SQLStorageManager/fork", () => {
		GLib.print (MISS_IMPL);
	});

	Test.add_func ("/SQLStorageManager/clone", () => {
		GLib.print (MISS_IMPL);
	});
}


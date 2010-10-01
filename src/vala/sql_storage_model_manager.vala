
namespace MidgardCR {

	public class SQLStorageModelManager : GLib.Object, Model, Executable, StorageExecutor, StorageModelManager {

		/* internal properties */
		internal unowned SQLStorageManager _storage_manager = null;
		internal NamespaceManager _ns_manager = null;
		internal unowned StorageModel[] _storage_models = null;
		internal unowned SchemaModel[] _schema_models = null;
		internal Model[] _models = null;
		internal SchemaModel _schema_model = null;
		internal StorageModel sql_storage_model = null;
		internal GLib.SList _query_slist = null;

		/* Model properties */
		/**
		 * SQLStorageModelManager doesn't hold parent model.
		 */	
		public Model? parent { 
			get { return null; }
			set { return; }
		}
		
		/**
		 * Namespace of the manager (if required)
		 */
                public string @namespace { get; set;  }

		/**
		 * Name of the manager (if required)
		 */
                public string name { get; set;  }

		/* properties */
		/**
		 * {@link NamespaceManager} of the manager
		 */
		public NamespaceManager namespace_manager { 
			get { return this._ns_manager; }
		}

		/**
		 * {@link StorageManager}
		 */
		public StorageManager storage_manager   { 
			get { return null; } 
		} 		

		/**
		 * Constructor
		 */
		public SQLStorageModelManager () {
			Object ();
			
			/* Initialize SchemaModel */
			this._schema_model = new SchemaModel ("SchemaModel");
			//this._schema_model.add_model (new SchemaModelProperty ("name", "string", ""));

			/* Initialize StorageModel */
			//this._storage_model = new StorageModel ("SchemaModel", "midgard_schema_type");
			//this._storage_model.add_model (new SQLStorageModelProperty ());				
				 	
		}

		/* destructor */
		~SQLStorageModelManager () {
			if (this._query_slist != null 
				&& this._query_slist.length () > 0) {
				this._query_slist.foreach (GLib.free);
			}	
		}

		/* Model methods */
		/**
                 * Associate new model 
                 *
                 * @param model {@link Model} to add
                 *
                 * @return {@link Model} instance (self reference)
                 */
		public Model add_model (Model model) {
			this._models += model;
			return this;
		}
				
		/**
                 * Get model by given name. 
		 * SQLStorageModelManager holds {@link SchemaModel} and {@link StorageModel} models,
		 * so accepted name by the one of Schema or Storage model.
	         * 
                 * @param name {@link Model} name to look for
                 *
                 * @return {@link Model} if found, null otherwise
                 */
                public unowned Model? get_model_by_name (string name) {
			return this._find_model_by_name (this._models, name);
		}

		/**
		 * List all models associated with with an instance.
		 * See list_storage_models() and list_schema_models().
		 *
		 * @return array of models or null
		 */
                public unowned Model[]? list_models () {
			return this._models;
		}

		/**
		 * Always returns null
		 */
                public ModelReflector get_reflector () {
			return null;
		}

		private unowned Model? _find_model_by_name (Model[] models, string name) {
			if (models == null)
				return null;

			foreach (unowned Model model in models) {
				if (model.name == name)
					return model;
			}
			return null;
		}

		/**
		 * Perform all checks required to mark instance as valid.
		 */
                public void is_valid () throws ValidationError {
			if (((MidgardCR.SQLStorageManager)this._storage_manager)._cnc == null)
				throw new MidgardCR.ValidationError.INTERNAL ("StorageManager not connected to any database"); 		
		}

		/* StorageExecutor methods */

		public bool exists () {
			return false;
		}

		/**
		 * Prepares create operation for all associated models.
		 * Valid SQL query (or prepared statement) is generated 
		 * in this method, so every model added after this method 
		 * call will be ignored and none of its data will be included in 
		 * executed query.
		 */
		public void prepare_create () throws ValidationError {
			this.is_valid ();

			foreach (Model model in this._models) {
				unowned Model model_found = this._find_model_by_name ((Model[])this._schema_models, model.name);
				if (model_found != null)
					throw new MidgardCR.ValidationError.NAME_DUPLICATED ("%s class already exists in schema table", model.name); 
			}
			MidgardCRCore.SQLStorageModelManager.prepare_create (this);	
		}

		private void _model_check_in_storage () throws ValidationError {
			bool found = false;
			string invalid_name = "";
			foreach (Model model in this._models) {
				unowned Model model_found = this._find_model_by_name ((Model[])this._schema_models, model.name);
				if (model_found == null)
					model_found = this._find_model_by_name ((Model[])this._storage_models, model.name);
				if (model_found != null 
					&& (((MidgardCR.SchemaModel) model_found)._id == ((MidgardCR.SchemaModel) model)._id)) {
					found = true;
					invalid_name = model.name;
					break;
				}
			}
			if (!found)
				throw new MidgardCR.ValidationError.NAME_INVALID ("No entry in schema or storage table found for given %s ", invalid_name); 
		}

		/**
		 * Prepares update operation.
		 */
                public void prepare_update () throws ValidationError {
			this.is_valid ();
			this._model_check_in_storage ();
		}

		/**
		 * Prepares save operation. 
		 */
                public void prepare_save () throws ValidationError {
			this.is_valid ();
			this._model_check_in_storage ();
		}

		/**
		 * Prepares remove operation.
		 */
                public void prepare_remove () throws ValidationError {
			this.is_valid ();
			this._model_check_in_storage ();
		}

		/**
		 * Prepares purge operation.
		 */
                public void prepare_purge () throws ValidationError {
			this.is_valid ();
			this._model_check_in_storage ();
		}

		/* Executable methods */
		/**
		 * Perform prepared operations.
		 *
		 * Executes SQL query (or queries) generated in prepare methods.
		 * There is no need to invoke execute per every prepare method.
		 * Any prepared query (or prepared statement) is kept and executed
		 * in this method, so there's no limit how many SQL queries might be 
		 * executed for underlying SQL storage engine.
		 */
		public void execute () throws ExecutableError {
			if (this._query_slist == null 
				|| (this._query_slist != null && this._query_slist.length() == 0))
				throw new MidgardCR.ExecutableError.COMMAND_INVALID_DATA ("No single prepared operation found");
			MidgardCRCore.SQLStorageModelManager.execute (this);
		}

		/* methods */
		/**
		 * Creates new StorageModel instance.
		 * 
		 * @param model, {@link SchemaModel} instance, which underlying 
		 * storage should be created for.
		 * @param location, name of the table which stores data of objects of the class
		 * represented by SchemaModel.
		 *
		 * @return StorageModel instance 
		 */
		public StorageModel create_storage_model (SchemaModel model, string location) {
			return null;
		}

		/**
		 * List all StorageModel models for which database entries already exist.
		 */
		public unowned StorageModel[]? list_storage_models () {
			return this._storage_models;
		}
		
		/**
		 * List all SchemaModel models for which database entries already exist.
		 */
		public unowned SchemaModel[]? list_schema_models () {
			return this._schema_models;
		}
	}
}
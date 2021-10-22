API stands for application programming interface 

API takes requests from the clients what they want and send the data client needed ,if the data can't be shared it will send message as it can't be shared 
API acts as medium between client and the web server consisting of data 


* WHY DO WE NEED API IN ANDROID *
> it allows communication between the server and the application .
> send and receives the response(data) from server to user and user to server .
> to access the data from the server .


* TYPES OF API *
> REST API - Representational state transfer .
> SOAP API - Simple Object Access Protocol.
> ASP.net

* REST API is mostly used API in the market Today.


* REST API implementation steps *
> First we have to create an project in android studio .

> we have add Internet Permission in Manifest.xml 
  we need internet because we have to access the data from the server using API .
  
>Add Retrofit Libraries  
 what is a retrofit ??
 : Retrofit is an build-in library or dependancy which is used to integrate HTTPS request .
 HTTP - Hyper Text Transfer Protocol 
 
 why do we need Retrofit ??
 : previously to access HTTP we would have a long and lengthy code ,to over come the problem the developers have created retrofit library , volly library etc 
 
 Adding the dependancies of retrofit and gson converter in app gradle in android studio 
 com.squareup.retrofit2:retrofit:2.9.0             // retrofit library dependancy //
 implementation 'com.squareup.retrofit2:converter-gson:latest.version'            // gson converter dependancy //
 
 
 
> Create Class for Retrofit instance  

public class ApiUtilities {                                            // we create class to get the retrofit instances ,we can name it as we want //
    private static  Retrofit retrofit =null;                          // initialize the retrofit //
    public static ApiInterface getApiInterface()                      // creating a getter to get it when we need //
    {
       /* when we want to get the retrofit instance we will always check whether the retrofit is null or not */
       /* if it is null it mean it doesn't have any data so  we create an new retrofit */
       /* new Retrofit creates a new retrofit and builder will the retrofit with the data we have given to it */
       /* we have to add the base url of the server we want to access so using >baseurl(here we use the url ) */
       /* now we use addConverterFactory to convert Json to Gson ,we convert because we get the data from the server in the form of Json which can't be used directly
         hence to convert into Gson which is understandable */
       /* and finally we return it when ever it is called */  
       
          if(retrofit==null)
            retrofit=new Retrofit.Builder ()
            .baseUrl ( ApiInterface.BASE_URL )
                    .addConverterFactory ( GsonConverterFactory.create () )
                    .build ();

        return retrofit.create (ApiInterface.class );
    }
}
 
 
> now creating interface for end points 
 create and interface class 
 
 /* mostly we use post and get in the interface */
 /* post is used to send some data to server */
 /* get is used when we want to get the data from server */
 
 public interface ApiInterface {
    static final String BASE_URL ="https://corona.lmao.ninja/v2/";
    @GET("countries")                                                     /* here we are getting data of countries from the server */
                                                                          /* we have place in get which data we want from the server */
    Call<List<CountryData>> getCountryData();                             /* here we create a list to represent them in recycler view 
                                                                             and data type should the name of the model clss created
                                                                             and get it */
}
 
 
> now we have to create a model class 
 in this class we have create constructer setters and getters for the variables initialized 
 
 /* all the names should be same as the names in the API */
 /* in the Json converter we can find the names */
 
 
 public class CountryData {
    private String updated;
    private String country;
    private String cases;
    private String todayCases;
    private String deaths;
    private String todayDeaths;
    private String recovered;
    private String todayRecovered;
    private String tests;
    private String active;
    private Map<String,String> countryInfo;

    public String getUpdated() {
        return updated;
    }

    public void setUpdated(String updated) {
        this.updated = updated;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public String getCases() {
        return cases;
    }

    public void setCases(String cases) {
        this.cases = cases;
    }

    public String getTodayCases() {
        return todayCases;
    }

    public void setTodayCases(String todayCases) {
        this.todayCases = todayCases;
    }

    public String getDeaths() {
        return deaths;
    }

    public void setDeaths(String deaths) {
        this.deaths = deaths;
    }

    public String getTodayDeaths() {
        return todayDeaths;
    }

    public void setTodayDeaths(String todayDeaths) {
        this.todayDeaths = todayDeaths;
    }

    public String getRecovered() {
        return recovered;
    }

    public void setRecovered(String recovered) {
        this.recovered = recovered;
    }

    public String getTodayRecovered() {
        return todayRecovered;
    }

    public void setTodayRecovered(String todayRecovered) {
        this.todayRecovered = todayRecovered;
    }

    public String getTests() {
        return tests;
    }

    public void setTests(String tests) {
        this.tests = tests;
    }

    public String getActive() {
        return active;
    }

    public void setActive(String active) {
        this.active = active;
    }

    public Map<String, String> getCountryInfo() {
        return countryInfo;
    }

    public void setCountryInfo(Map<String, String> countryInfo) {
        this.countryInfo = countryInfo;
    }

    public CountryData(String updated, String country, String cases, String todayCases, String deaths, String todayDeaths, String recovered, String todayRecovered, String tests, String active, Map<String, String> countryInfo) {
        this.updated = updated;
        this.country = country;
        this.cases = cases;
        this.todayCases = todayCases;
        this.deaths = deaths;
        this.todayDeaths = todayDeaths;
        this.recovered = recovered;
        this.todayRecovered = todayRecovered;
        this.tests = tests;
        this.active = active;
        this.countryInfo = countryInfo;
    }
}
 
 
> call the API in the activity 

 public class CountryActivity extends AppCompatActivity {
    private RecyclerView recyclerView;
    private List<CountryData> list;
    private ProgressDialog dialog;
    private EditText searchbar;
    private CountryAdapter Adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate ( savedInstanceState );
        setContentView ( R.layout.activity_country);


        recyclerView=findViewById ( R.id.countries );
        list=new ArrayList<> ();
        searchbar=findViewById ( R.id.searchbar );

        recyclerView.setLayoutManager ( new LinearLayoutManager ( this ) );
        recyclerView.setHasFixedSize (true);

        Adapter=new CountryAdapter ( this,list );                      /* we have to create an adapter to set data in recycler view */
        recyclerView.setAdapter ( Adapter );                           /* setting data in the recycler view */


        dialog=new ProgressDialog ( this );
        dialog.setMessage ( "LOADING" );
        dialog.setCancelable ( false );
        dialog.show ();
        
        /* getting the apiinterface created and getting the data we need and calling list the list whenever we get the data from server */

        ApiUtilities.getApiInterface ().getCountryData ().enqueue ( new Callback<List<CountryData>> () {
        
        /* if we get any data from the server the below method executes */ 
            @Override
            public void onResponse(Call<List<CountryData>> call, Response<List<CountryData>> response) {
            
            /* response carries the data , we add the data to the list */
                list.addAll ( response.body () );
                Adapter.notifyDataSetChanged ();
                dialog.dismiss ();

            }
            
            /* we no data is received then the below method is executed */
            @Override
            public void onFailure(Call<List<CountryData>> call, Throwable t) {
                dialog.dismiss ();
                Toast.makeText (CountryActivity.this,"Error"+t.getMessage (),Toast.LENGTH_SHORT).show ();
            }
        } );

        searchbar.addTextChangedListener ( new TextWatcher () {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                filter(s.toString ());

            }
        } );
    }

    private void filter(String text) {
        List<CountryData> filterlist=new ArrayList<> ();
        for(CountryData item : list)
        {
            if(item.getCountry ().toLowerCase ().contains ( text.toLowerCase () ))
            {
                filterlist.add ( item );
            }
        }
        Adapter.filterList ( filterlist );
    }
}
 


/* adapter for the country activity */
 public class CountryAdapter extends RecyclerView.Adapter<CountryAdapter.CountryViewHolder>
{
    private Context context;
    private List<CountryData> list;

    public CountryAdapter(Context context, List<CountryData> list) {
        this.context = context;
        this.list = list;
    }

    @NonNull
    @org.jetbrains.annotations.NotNull
    @Override
    public CountryViewHolder onCreateViewHolder(@NonNull @org.jetbrains.annotations.NotNull ViewGroup parent, int viewType) {
        View view= LayoutInflater.from ( context ).inflate ( R.layout.country_item_name,parent,false );


        return new CountryViewHolder ( view );
    }

    @Override
    public void onBindViewHolder(@NonNull @org.jetbrains.annotations.NotNull CountryAdapter.CountryViewHolder holder, int position) {

        CountryData data=list.get ( position );
        holder.countryCases.setText ( NumberFormat.getInstance ().format ( Integer.parseInt ( data.getCases () ) ) );
        holder.countryName.setText ( data.getCountry () );
        holder.snum.setText ( String.valueOf ( position+1 ) );
        Map<String,String> img=data.getCountryInfo ();
        Glide.with ( context ).load ( img.get ( "flag" ) ).into ( holder.imageView );


        holder.itemView.setOnClickListener ( v -> {
            Intent intent =new Intent (context,MainActivity.class);
            intent.putExtra ( "country",data.getCountry ());
            context.startActivity ( intent );

        } );
    }
    public void filterList(List<CountryData> filterList)
    {
        list=filterList;
        notifyDataSetChanged ();
    }


    @Override
    public int getItemCount() {
        return list.size ();
    }

    public class CountryViewHolder extends RecyclerView.ViewHolder {
        private TextView snum,countryName,countryCases;
        private ImageView imageView;

        public CountryViewHolder(@NonNull @org.jetbrains.annotations.NotNull View itemView) {
            super ( itemView );
            snum=itemView.findViewById ( R.id.snum );
            countryName=itemView.findViewById ( R.id.countryName );
            countryCases=itemView.findViewById ( R.id.countryCases );
            imageView=itemView.findViewById ( R.id.countryImage );
        }
    }

}
 
 

/* home view of the application */
 
 
 public class MainActivity extends AppCompatActivity {
    private TextView totalConfirm,totalActive,totalRecovered,totalDeath;
    private TextView todayConfirm,todayRecovered,todayDeath,date,totalTests;
    private PieChart pieChart;

    private List<CountryData> list;
    String country="India";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate ( savedInstanceState );
        setContentView ( R.layout.activity_main );
        list=new ArrayList<> ();

        if(getIntent ().getStringExtra ( "country" )!=null)              /* getting the country data to be represented using intent */
            country=getIntent ().getStringExtra ( "country" );


        init();
        TextView cname =findViewById ( R.id.cname );
        cname.setText ( country );

      /* on clicking the country data it moves to the countries list recycler view */
        cname.setOnClickListener ( v -> startActivity ( new Intent (MainActivity.this,CountryActivity.class) ) );    


        ApiUtilities.getApiInterface ().getCountryData ().enqueue ( new Callback<List<CountryData>> () {
            @Override
            public void onResponse(Call<List<CountryData>> call, Response<List<CountryData>> response) {
                list.addAll (response.body ()  );
                for(int i=0;i<list.size();i++)
                {
                   if(list.get ( i ).getCountry ().equals ( country) )
                    {
                        int confirm=Integer.parseInt ( list.get ( i ).getCases () );
                        int active=Integer.parseInt ( list.get ( i ).getActive () );
                        int recovered=Integer.parseInt ( list.get ( i ).getRecovered () );
                        int death=Integer.parseInt ( list.get ( i ).getDeaths () );

                        totalActive.setText ( NumberFormat.getInstance ().format ( active ) );
                        totalConfirm.setText ( NumberFormat.getInstance ().format ( confirm ) );
                        totalRecovered.setText ( NumberFormat.getInstance ().format ( recovered) );
                        totalDeath.setText ( NumberFormat.getInstance ().format ( death ) );

                        todayConfirm.setText ( NumberFormat.getInstance ().format ( Integer.parseInt ( list.get ( i ).getTodayCases () ) ) );
                        todayRecovered.setText ( NumberFormat.getInstance ().format ( Integer.parseInt ( list.get ( i ).getTodayRecovered () ) ) );
                        todayDeath.setText ( NumberFormat.getInstance ().format ( Integer.parseInt ( list.get ( i ).getTodayDeaths () ) ) );
                        totalTests.setText ( NumberFormat.getInstance ().format ( Integer.parseInt ( list.get ( i ).getTests () ) ) );

                        setText(list.get ( i ).getUpdated ());

                        pieChart.addPieSlice ( new PieModel ("Confirm",confirm,getResources ().getColor ( R.color.red )) );
                        pieChart.addPieSlice ( new PieModel ("Active",active,getResources ().getColor ( R.color.blue_pie )) );
                        pieChart.addPieSlice ( new PieModel ("Recovered",recovered,getResources ().getColor ( R.color.green_pie )) );
                        pieChart.addPieSlice ( new PieModel ("Death",death,getResources ().getColor ( R.color.yellow )) );
                        pieChart.startAnimation ();

                    }

                }
            }

            @Override
            public void onFailure(Call<List<CountryData>> call, Throwable t) {
                Toast.makeText ( MainActivity.this,"Error" + t.getMessage (),Toast.LENGTH_SHORT).show ();

            }
        } );
    }

    private void setText(String updated) {
        DateFormat format = new SimpleDateFormat ( "MMM dd,yyyy" );

        long milliseconds =Long.parseLong ( updated );
        Calendar calendar=Calendar.getInstance ();
        calendar.setTimeInMillis ( milliseconds );

        date.setText ( "Updated at"+format.format ( calendar.getTime () ) );
    }

    private void init()
    {
        todayConfirm=findViewById ( R.id.todayConfirm );
        totalConfirm=findViewById ( R.id.totalConfirm );
        totalActive=findViewById ( R.id.totalActive );
        totalRecovered=findViewById ( R.id.totalRecovered );
        todayRecovered=findViewById ( R.id.todayRecovered );
        totalDeath=findViewById ( R.id.totalDeath );
        todayDeath=findViewById ( R.id.todayDeath );
        pieChart=findViewById(R.id.piechart);
        totalTests=findViewById ( R.id.totalTests );
        date=findViewById ( R.id.date );
    }
}
 
 
